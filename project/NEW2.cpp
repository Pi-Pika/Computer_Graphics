#include <GL/glut.h>
#include <math.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <string>

// --- Global Variables ---
GLuint backWallTexture = 0; // Texture ID for back wall image
GLuint photoFrameTexture = 0; // Texture ID for photo frame
float fanAngle = 0.0f;
bool isFanOn = false;
bool isLampOn = false;
bool isPCOn = false;
bool isNight = false; // New: Day/Night cycle
bool isDoorOpen = false;
bool isWindowOpen = false;
float doorAngle = 0.0f; // Door opening angle (0 to 90 degrees)
float windowAngle = 0.0f; // Window opening angle (0 to 45 degrees)
bool isLEDOn = false; // LED strip on back wall
bool isTVOn = false; // LED TV on/off
float tvAnimTime = 0.0f; // Animation timer for TV patterns
int tvChannel = 1; // TV channel (1-5 different patterns)
const int MAX_CHANNELS = 5;
int currentPhotoIndex = 0; // Current photo displayed in frame
std::vector<std::string> photoList; // List of photo files

// --- Camera Variables for 360 View ---
float camX = 0.0f, camZ = 35.0f; // Camera position - zoomed out for full room view from outside
float angle = 0.0f;              // Angle of rotation for the camera direction
float lx = sin(angle), lz = -cos(angle);     // Actual vector representing the camera's direction

// --- Texture Loading Function ---
GLuint loadBMPTexture(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cout << "Failed to load texture: " << filename << std::endl;
        return 0;
    }

    // Read BMP header
    unsigned char header[54];
    file.read((char*)header, 54);

    // Get image dimensions
    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int imageSize = width * height * 3;

    // Read image data
    std::vector<unsigned char> data(imageSize);
    file.read((char*)data.data(), imageSize);
    file.close();

    // Convert BGR to RGB
    for (int i = 0; i < imageSize; i += 3) {
        std::swap(data[i], data[i + 2]);
    }

    // Generate texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());

    std::cout << "Texture loaded successfully: " << filename << " (" << width << "x" << height << ")" << std::endl;
    return textureID;
}

// --- Simple JPG loader using built-in Windows APIs ---
GLuint loadJPGTexture(const char* filename) {
    // Load JPG using Windows GDI+
    // For simplicity, we'll just warn the user
    std::cout << "JPG file: " << filename << std::endl;
    std::cout << "Converting JPG to BMP format..." << std::endl;

    // Try PowerShell conversion as fallback
    char command[512];
    char tempBmp[256];

    // Create temp BMP filename
    snprintf(tempBmp, sizeof(tempBmp), "%s_temp.bmp", filename);

    // Use PowerShell to convert using .NET
    snprintf(command, sizeof(command),
        "powershell -NoProfile -Command \"[System.Reflection.Assembly]::LoadWithPartialName('System.Drawing'); "
        "$img = [System.Drawing.Image]::FromFile('%s'); "
        "$bmp = New-Object System.Drawing.Bitmap(1024, 768); "
        "$g = [System.Drawing.Graphics]::FromImage($bmp); "
        "$g.DrawImage($img, 0, 0, 1024, 768); "
        "$g.Dispose(); "
        "$bmp.Save('%s', [System.Drawing.Imaging.ImageFormat]::Bmp); "
        "$bmp.Dispose(); "
        "$img.Dispose()\" 2>nul",
        filename, tempBmp);

    int result = system(command);

    if (result == 0 && GetFileAttributesA(tempBmp) != INVALID_FILE_ATTRIBUTES) {
        std::cout << "Successfully converted JPG to temporary BMP" << std::endl;
        GLuint texID = loadBMPTexture(tempBmp);
        // Delete temp file after loading
        DeleteFileA(tempBmp);
        return texID;
    }

    std::cout << "JPG conversion failed. Using fallback white texture." << std::endl;
    return 0;
}

// --- Load photos from album folder ---
void loadPhotosFromFolder(const char* folderPath) {
    photoList.clear();

    // Load both BMP and JPG files
    WIN32_FIND_DATAA findFileData;
    HANDLE findHandle;
    char searchPath[256];

    // First search for BMP files
    snprintf(searchPath, sizeof(searchPath), "%s/*.bmp", folderPath);

    findHandle = FindFirstFileA(searchPath, &findFileData);

    if (findHandle != INVALID_HANDLE_VALUE) {
        do {
            std::string filename = findFileData.cFileName;
            if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                char fullPath[256];
                snprintf(fullPath, sizeof(fullPath), "%s/%s", folderPath, filename.c_str());
                photoList.push_back(fullPath);
                std::cout << "Found BMP photo: " << fullPath << std::endl;
            }
        } while (FindNextFileA(findHandle, &findFileData));
        FindClose(findHandle);
    }

    // Search for JPG files
    snprintf(searchPath, sizeof(searchPath), "%s/*.jpg", folderPath);

    findHandle = FindFirstFileA(searchPath, &findFileData);

    if (findHandle != INVALID_HANDLE_VALUE) {
        do {
            std::string filename = findFileData.cFileName;
            if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                char fullPath[256];
                snprintf(fullPath, sizeof(fullPath), "%s/%s", folderPath, filename.c_str());
                photoList.push_back(fullPath);
                std::cout << "Found JPG photo: " << fullPath << std::endl;
            }
        } while (FindNextFileA(findHandle, &findFileData));
        FindClose(findHandle);
    }

    // Search for JPEG files
    snprintf(searchPath, sizeof(searchPath), "%s/*.jpeg", folderPath);

    findHandle = FindFirstFileA(searchPath, &findFileData);

    if (findHandle != INVALID_HANDLE_VALUE) {
        do {
            std::string filename = findFileData.cFileName;
            if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                char fullPath[256];
                snprintf(fullPath, sizeof(fullPath), "%s/%s", folderPath, filename.c_str());
                photoList.push_back(fullPath);
                std::cout << "Found JPEG photo: " << fullPath << std::endl;
            }
        } while (FindNextFileA(findHandle, &findFileData));
        FindClose(findHandle);
    }

    if (!photoList.empty()) {
        std::cout << "Found " << photoList.size() << " photos in album folder" << std::endl;

        // Load first photo (determine format and use appropriate loader)
        std::string firstPhoto = photoList[0];
        if (firstPhoto.find(".jpg") != std::string::npos ||
            firstPhoto.find(".jpeg") != std::string::npos ||
            firstPhoto.find(".JPG") != std::string::npos ||
            firstPhoto.find(".JPEG") != std::string::npos) {
            photoFrameTexture = loadJPGTexture(firstPhoto.c_str());
        }
        else {
            photoFrameTexture = loadBMPTexture(firstPhoto.c_str());
        }
        std::cout << "Loaded first photo: " << firstPhoto << " Texture ID: " << photoFrameTexture << std::endl;
    }
    else {
        std::cout << "No photos found in album folder." << std::endl;
    }
}

// --- Helper Functions to Draw 3D Shapes ---

void drawCube(float r, float g, float b) {
    glColor3f(r, g, b);
    glutSolidCube(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glutWireCube(1.01f);
}

// Draw textured tiles floor with a checkerboard pattern
void drawTexturedTilesFloor(float sizeX, float sizeZ, int tilesX, int tilesZ, 
                            float r1, float g1, float b1, float r2, float g2, float b2) {
    float tileWidth = sizeX / tilesX;
    float tileDepth = sizeZ / tilesZ;
    
    glPushMatrix();
    glTranslatef(-sizeX / 2.0f, 0.0f, -sizeZ / 2.0f);
    
    for (int x = 0; x < tilesX; x++) {
        for (int z = 0; z < tilesZ; z++) {
            // Alternate colors for checkerboard pattern
            int checkerboard = (x + z) % 2;
            
            if (checkerboard == 0) {
                glColor3f(r1, g1, b1);
            } else {
                glColor3f(r2, g2, b2);
            }
            
            glPushMatrix();
            glTranslatef(x * tileWidth + tileWidth / 2.0f, 0.0f, z * tileDepth + tileDepth / 2.0f);
            
            // Draw tile with outline
            glBegin(GL_QUADS);
            glVertex3f(-tileWidth / 2.0f, 0.01f, -tileDepth / 2.0f);
            glVertex3f(tileWidth / 2.0f, 0.01f, -tileDepth / 2.0f);
            glVertex3f(tileWidth / 2.0f, 0.01f, tileDepth / 2.0f);
            glVertex3f(-tileWidth / 2.0f, 0.01f, tileDepth / 2.0f);
            glEnd();
            
            // Tile outline for better definition
            glColor3f(0.3f, 0.3f, 0.3f);
            glLineWidth(1.5f);
            glBegin(GL_LINE_LOOP);
            glVertex3f(-tileWidth / 2.0f, 0.02f, -tileDepth / 2.0f);
            glVertex3f(tileWidth / 2.0f, 0.02f, -tileDepth / 2.0f);
            glVertex3f(tileWidth / 2.0f, 0.02f, tileDepth / 2.0f);
            glVertex3f(-tileWidth / 2.0f, 0.02f, tileDepth / 2.0f);
            glEnd();
            glLineWidth(1.0f);
            
            glPopMatrix();
        }
    }
    
    glPopMatrix();
}

// Requirement: Midpoint Circle Algorithm (For Clock)
void drawCircle3D(float xc, float yc, float z, float r) {
    float x = 0, y = r;
    float d = 3 - 2 * r;
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    while (y >= x) {
        glVertex3f(xc + x * 0.05f, yc + y * 0.05f, z);
        glVertex3f(xc - x * 0.05f, yc + y * 0.05f, z);
        glVertex3f(xc + x * 0.05f, yc - y * 0.05f, z);
        glVertex3f(xc - x * 0.05f, yc - y * 0.05f, z);
        glVertex3f(xc + y * 0.05f, yc + x * 0.05f, z);
        glVertex3f(xc - y * 0.05f, yc + x * 0.05f, z);
        glVertex3f(xc + y * 0.05f, yc - x * 0.05f, z);
        glVertex3f(xc - y * 0.05f, yc - x * 0.05f, z);
        x++;
        if (d > 0) {
            y--; d = d + 4 * (x - y) + 10;
        }
        else {
            d = d + 4 * x + 6;
        }
    }
    glEnd();
}

// Requirement: Bresenham's Line Algorithm (For Clock Hands)
void drawLine3D(float x1, float y1, float x2, float y2, float z) {
    float dx = abs(x2 - x1), dy = abs(y2 - y1);
    float p = 2 * dy - dx;
    float twoDy = 2 * dy, twoDyDx = 2 * (dy - dx);
    float x, y, xEnd;
    if (x1 > x2) { x = x2; y = y2; xEnd = x1; }
    else { x = x1; y = y1; xEnd = x2; }

    glPointSize(3.0f);
    glBegin(GL_POINTS);
    glVertex3f(x * 0.05f, y * 0.05f, z);
    while (x < xEnd) {
        x++;
        if (p < 0) p += twoDy;
        else { y++; p += twoDyDx; }
        glVertex3f(x * 0.05f, y * 0.05f, z);
    }
    glEnd();
}

// --- Enhanced Bookshelf with Realistic Details ---
void drawBookshelf() {
    glPushMatrix();
    glTranslatef(9.5f, 2.0f, -7.0f); // Aligned with bed

    // Side panels (left and right)
    glPushMatrix();
    glTranslatef(-1.3f, 0.0f, 0.0f);
    glScalef(0.15f, 5.0f, 1.2f);
    drawCube(0.35f, 0.22f, 0.12f); // Dark wood
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.3f, 0.0f, 0.0f);
    glScalef(0.15f, 5.0f, 1.2f);
    drawCube(0.35f, 0.22f, 0.12f);
    glPopMatrix();

    // Back panel
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.5f);
    glScalef(2.45f, 5.0f, 0.1f);
    drawCube(0.4f, 0.25f, 0.15f);
    glPopMatrix();

    // Top and bottom
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f);
    glScalef(2.6f, 0.2f, 1.2f);
    drawCube(0.35f, 0.22f, 0.12f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -2.5f, 0.0f);
    glScalef(2.6f, 0.2f, 1.2f);
    drawCube(0.35f, 0.22f, 0.12f);
    glPopMatrix();

    // 4 Shelves
    float shelfPositions[] = { -1.5f, -0.3f, 0.9f, 2.1f };
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(0.0f, shelfPositions[i], 0.0f);
        glScalef(2.4f, 0.15f, 1.1f);
        drawCube(0.38f, 0.24f, 0.14f);
        glPopMatrix();
    }

    // Enhanced book collection with variety
    float bookColors[15][3] = {
        {0.8,0.1,0.1}, {0.1,0.5,0.1}, {0.1,0.2,0.8}, {0.6,0.4,0.1}, {0.7,0.1,0.5},
        {0.9,0.6,0.1}, {0.2,0.6,0.6}, {0.5,0.2,0.7}, {0.8,0.3,0.2}, {0.3,0.7,0.3},
        {0.6,0.2,0.4}, {0.2,0.4,0.8}, {0.8,0.5,0.0}, {0.5,0.3,0.6}, {0.7,0.2,0.2}
    };

    // Draw books on each shelf
    for (int shelf = 0; shelf < 4; shelf++) {
        float yPos = shelfPositions[shelf] + 0.4f;
        int booksOnShelf = 4 + (shelf % 2);

        for (int i = 0; i < booksOnShelf; i++) {
            glPushMatrix();
            float xOffset = -1.0f + (i * (2.0f / booksOnShelf));
            glTranslatef(xOffset, yPos, 0.15f);

            // Random book dimensions for variety
            float width = 0.12f + (i % 3) * 0.04f;
            float height = 0.65f + ((i + shelf) % 3) * 0.15f;
            float depth = 0.6f + (i % 2) * 0.15f;

            // Slight random tilt for realism
            float tilt = ((i + shelf) % 3 - 1) * 3.0f;
            glRotatef(tilt, 0.0f, 0.0f, 1.0f);

            glScalef(width, height, depth);
            int colorIndex = (shelf * 3 + i) % 15;
            drawCube(bookColors[colorIndex][0], bookColors[colorIndex][1], bookColors[colorIndex][2]);
            glPopMatrix();

            // Book spine details (thin line)
            glPushMatrix();
            glTranslatef(xOffset, yPos, 0.5f);
            glRotatef(tilt, 0.0f, 0.0f, 1.0f);
            glScalef(width * 0.9f, height * 0.95f, 0.02f);
            drawCube(bookColors[colorIndex][0] * 0.7f,
                bookColors[colorIndex][1] * 0.7f,
                bookColors[colorIndex][2] * 0.7f);
            glPopMatrix();
        }
    }

    // Decorative items on top shelf
    // Small plant pot
    glPushMatrix();
    glTranslatef(-0.8f, 2.8f, 0.2f);
    glColor3f(0.6f, 0.3f, 0.1f);
    glutSolidCube(0.3f);
    glTranslatef(0.0f, 0.25f, 0.0f);
    glColor3f(0.1f, 0.6f, 0.2f);
    glutSolidSphere(0.2f, 10, 10);
    glPopMatrix();

    // Picture frame
    glPushMatrix();
    glTranslatef(0.7f, 2.8f, 0.15f);
    glScalef(0.4f, 0.5f, 0.05f);
    drawCube(0.8f, 0.7f, 0.3f);
    glPopMatrix();

    glPopMatrix();
}

void drawWallpaper() {
    if (backWallTexture == 0) return; // Only draw if texture is loaded

    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, backWallTexture);
    glColor3f(1.0f, 1.0f, 1.0f);

    // BACK WALL - Textured (single image, no repeat, extended to cover LED area)
    glPushMatrix();
    glTranslatef(0.0f, 3.5f, -12.2f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-12.5f, -7.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(12.5f, -7.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(12.5f, 10.5f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-12.5f, 10.5f, 0.0f);
    glEnd();
    glPopMatrix();

    // RIGHT WALL - Textured with window cutout
    // Window is at Z=0, Y=6, width=6.2 (±3.1), height=4.9 (±2.45)

    // Bottom section (below window) - full width
    glPushMatrix();
    glTranslatef(12.2f, 6.0f, 0.0f);
    glRotatef(90, 0, 1, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-12.5f, -7.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(12.5f, -7.0f, 0.0f);
    glTexCoord2f(1.0f, 0.325f); glVertex3f(12.5f, -2.45f, 0.0f);
    glTexCoord2f(0.0f, 0.325f); glVertex3f(-12.5f, -2.45f, 0.0f);
    glEnd();
    glPopMatrix();

    // Top section (above window) - full width
    glPushMatrix();
    glTranslatef(12.2f, 6.0f, 0.0f);
    glRotatef(90, 0, 1, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.675f); glVertex3f(-12.5f, 2.45f, 0.0f);
    glTexCoord2f(1.0f, 0.675f); glVertex3f(12.5f, 2.45f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(12.5f, 7.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-12.5f, 7.0f, 0.0f);
    glEnd();
    glPopMatrix();

    // Left section (left of window) - middle height only
    glPushMatrix();
    glTranslatef(12.2f, 6.0f, 0.0f);
    glRotatef(90, 0, 1, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.325f); glVertex3f(-12.5f, -2.45f, 0.0f);
    glTexCoord2f(0.376f, 0.325f); glVertex3f(-3.1f, -2.45f, 0.0f);
    glTexCoord2f(0.376f, 0.675f); glVertex3f(-3.1f, 2.45f, 0.0f);
    glTexCoord2f(0.0f, 0.675f); glVertex3f(-12.5f, 2.45f, 0.0f);
    glEnd();
    glPopMatrix();

    // Right section (right of window) - middle height only
    glPushMatrix();
    glTranslatef(12.2f, 6.0f, 0.0f);
    glRotatef(90, 0, 1, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.624f, 0.325f); glVertex3f(3.1f, -2.45f, 0.0f);
    glTexCoord2f(1.0f, 0.325f); glVertex3f(12.5f, -2.45f, 0.0f);
    glTexCoord2f(1.0f, 0.675f); glVertex3f(12.5f, 2.45f, 0.0f);
    glTexCoord2f(0.624f, 0.675f); glVertex3f(3.1f, 2.45f, 0.0f);
    glEnd();
    glPopMatrix();

    // LEFT WALL - Textured (single image, no repeat)
    glPushMatrix();
    glTranslatef(-12.2f, 6.0f, 0.0f);
    glRotatef(-90, 0, 1, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-12.5f, -7.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(12.5f, -7.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(12.5f, 7.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-12.5f, 7.0f, 0.0f);
    glEnd();
    glPopMatrix();

    // FRONT WALL - Textured (cutout for door panel area)
    // Door cutout: X from -7.8 to -4.2, Y from -0.4 to 5.4

    // Left section (from left edge to door)
    glPushMatrix();
    glTranslatef(0.0f, 6.0f, 12.2f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-12.5f, -7.0f, 0.0f);
    glTexCoord2f(0.188f, 0.0f); glVertex3f(-7.8f, -7.0f, 0.0f);
    glTexCoord2f(0.188f, 1.0f); glVertex3f(-7.8f, 7.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-12.5f, 7.0f, 0.0f);
    glEnd();
    glPopMatrix();

    // Right section (from door to right edge)
    glPushMatrix();
    glTranslatef(0.0f, 6.0f, 12.2f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.332f, 0.0f); glVertex3f(-4.2f, -7.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(12.5f, -7.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(12.5f, 7.0f, 0.0f);
    glTexCoord2f(0.332f, 1.0f); glVertex3f(-4.2f, 7.0f, 0.0f);
    glEnd();
    glPopMatrix();

    // Top section (above door, Y from 5.4 to 7.0)
    glPushMatrix();
    glTranslatef(0.0f, 6.0f, 12.2f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.188f, 0.886f); glVertex3f(-7.8f, -0.4f, 0.0f);
    glTexCoord2f(0.332f, 0.886f); glVertex3f(-4.2f, -0.4f, 0.0f);
    glTexCoord2f(0.332f, 1.0f); glVertex3f(-4.2f, 7.0f, 0.0f);
    glTexCoord2f(0.188f, 1.0f); glVertex3f(-7.8f, 7.0f, 0.0f);
    glEnd();
    glPopMatrix();



    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void drawLEDStrip() {
    glPushMatrix();
    glTranslatef(0.0f, 11.0f, -12.3f); // Top of back wall

    if (isLEDOn) {
        // LED strip glowing
        glColor3f(1.0f, 0.3f, 0.8f); // Bright pink/purple glow

        // Main LED strip
        glPushMatrix();
        glScalef(20.0f, 0.3f, 0.2f);
        glutSolidCube(1.0f);
        glPopMatrix();

        // Individual LED lights along the strip
        for (float x = -9.0f; x <= 9.0f; x += 1.5f) {
            glPushMatrix();
            glTranslatef(x, 0.0f, 0.0f);
            glColor3f(1.0f, 0.2f, 0.7f); // Bright LED color
            glutSolidSphere(0.2f, 10, 10);
            glPopMatrix();
        }

        // Add light source for LED
        GLfloat ledLightPos[] = { 0.0f, 11.0f, -12.0f, 1.0f };
        GLfloat ledLightColor[] = { 1.0f, 0.4f, 0.8f, 1.0f };
        glLightfv(GL_LIGHT2, GL_POSITION, ledLightPos);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, ledLightColor);
        glEnable(GL_LIGHT2);
    }
    else {
        // LED strip off (dark gray)
        glColor3f(0.2f, 0.2f, 0.2f);
        glPushMatrix();
        glScalef(20.0f, 0.3f, 0.2f);
        glutSolidCube(1.0f);
        glPopMatrix();

        glDisable(GL_LIGHT2);
    }

    glPopMatrix();
}

void drawRoom() {
    // Textured tiles floor (25x25) with checkerboard pattern
    glPushMatrix();
    glTranslatef(0.0f, -0.95f, 0.0f);
    // White tiles and light gray tiles for a modern look
    drawTexturedTilesFloor(25.0f, 25.0f, 10, 10, 
                           0.95f, 0.95f, 0.95f,  // Light gray/white
                           0.75f, 0.75f, 0.75f); // Medium gray
    glPopMatrix();

    // Rug
    glPushMatrix();
    glTranslatef(0.0f, -0.7f, 0.0f);
    glScalef(8.0f, 0.1f, 12.0f);
    drawCube(0.6f, 0.2f, 0.2f); // Red Rug
    glPopMatrix();

    // Back Wall - Always draw as base (covers entire height including LED area)
    glPushMatrix();
    glTranslatef(0.0f, 4.0f, -12.5f);
    glScalef(25.0f, 17.0f, 0.5f);
    drawCube(0.95f, 0.95f, 0.90f);
    glPopMatrix();

    // Base walls (behind texture) - only if no texture loaded
    if (backWallTexture == 0) {

        // Left Wall
        glPushMatrix();
        glTranslatef(-12.5f, 6.0f, 0.0f);
        glScalef(0.5f, 14.0f, 25.0f);
        drawCube(0.95f, 0.95f, 0.90f);
        glPopMatrix();

        // Right Wall - Bottom section (below window, Y from -1 to 3.55)
        glPushMatrix();
        glTranslatef(12.5f, 1.275f, 0.0f);
        glScalef(0.5f, 4.55f, 25.0f);
        drawCube(0.95f, 0.95f, 0.90f);
        glPopMatrix();

        // Right Wall - Top section (above window, Y from 8.45 to 13)
        glPushMatrix();
        glTranslatef(12.5f, 10.725f, 0.0f);
        glScalef(0.5f, 4.55f, 25.0f);
        drawCube(0.95f, 0.95f, 0.90f);
        glPopMatrix();

        // Right Wall - Left section (left of window, Z from -12.5 to -3.1)
        glPushMatrix();
        glTranslatef(12.5f, 6.0f, -7.8f);
        glScalef(0.5f, 4.9f, 9.4f);
        drawCube(0.95f, 0.95f, 0.90f);
        glPopMatrix();

        // Right Wall - Right section (right of window, Z from 3.1 to 12.5)
        glPushMatrix();
        glTranslatef(12.5f, 6.0f, 7.8f);
        glScalef(0.5f, 4.9f, 9.4f);
        drawCube(0.95f, 0.95f, 0.90f);
        glPopMatrix();

        // Front Wall - with door cutout
        // Door panel area: X from -7.8 to -4.2, Y from -0.4 to 5.4

        // Left section (from left edge X=-12.5 to door left X=-7.8)
        glPushMatrix();
        glTranslatef(-10.15f, 6.0f, 12.5f);
        glScalef(4.7f, 14.0f, 0.5f);
        drawCube(0.95f, 0.95f, 0.90f);
        glPopMatrix();

        // Right section (from door right X=-4.2 to right edge X=12.5)
        glPushMatrix();
        glTranslatef(4.15f, 6.0f, 12.5f);
        glScalef(16.7f, 14.0f, 0.5f);
        drawCube(0.95f, 0.95f, 0.90f);
        glPopMatrix();        // Top section (above door, Y from 5.4 to 13)
        glPushMatrix();
        glTranslatef(-6.0f, 9.2f, 12.5f);
        glScalef(3.5f, 7.6f, 0.5f);
        drawCube(0.95f, 0.95f, 0.90f);
        glPopMatrix();

        // Bottom section (below door, Y from -1 to -0.4)
        glPushMatrix();
        glTranslatef(-6.0f, -0.7f, 12.5f);
        glScalef(3.5f, 0.6f, 0.5f);
        drawCube(0.95f, 0.95f, 0.90f);
        glPopMatrix();
    }

    // Add wallpaper texture to all walls
    drawWallpaper();
}

void drawDoor() {
    glPushMatrix();
    glTranslatef(-6.0f, 2.5f, 12.5f); // Front wall position

    // Door frame (just the outer frame, not solid - so you can see through)
    // Left frame piece
    glPushMatrix();
    glTranslatef(-1.65f, 0.0f, 0.0f);
    glScalef(0.2f, 6.0f, 0.3f);
    drawCube(0.3f, 0.2f, 0.1f); // Dark wood frame
    glPopMatrix();

    // Right frame piece
    glPushMatrix();
    glTranslatef(1.65f, 0.0f, 0.0f);
    glScalef(0.2f, 6.0f, 0.3f);
    drawCube(0.3f, 0.2f, 0.1f);
    glPopMatrix();

    // Top frame piece
    glPushMatrix();
    glTranslatef(0.0f, 2.9f, 0.0f);
    glScalef(3.5f, 0.2f, 0.3f);
    drawCube(0.3f, 0.2f, 0.1f);
    glPopMatrix();

    // Bottom threshold
    glPushMatrix();
    glTranslatef(0.0f, -2.9f, 0.0f);
    glScalef(3.5f, 0.2f, 0.3f);
    drawCube(0.25f, 0.15f, 0.08f);
    glPopMatrix();

    // Door panel with rotation animation (outer side - darker wood)
    glPushMatrix();
    glTranslatef(-1.75f, 0.0f, 0.0f); // Move to hinge position
    glRotatef(-doorAngle, 0.0f, 1.0f, 0.0f); // Rotate around hinge
    glTranslatef(1.75f, 0.0f, 0.0f); // Move back

    glTranslatef(0.0f, 0.0f, -0.2f);
    glScalef(3.2f, 5.7f, 0.2f);
    drawCube(0.5f, 0.35f, 0.2f); // Medium wood
    glPopMatrix();

    // Door inner side (lighter color, visible when door opens)
    glPushMatrix();
    glTranslatef(-1.75f, 0.0f, 0.0f);
    glRotatef(-doorAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(1.75f, 0.0f, 0.0f);

    glTranslatef(0.0f, 0.0f, -0.4f); // Inside face
    glScalef(3.2f, 5.7f, 0.01f);
    drawCube(0.6f, 0.5f, 0.35f); // Lighter interior color
    glPopMatrix();

    // Door handle (rotates with door)
    glPushMatrix();
    glTranslatef(-1.75f, 0.0f, 0.0f);
    glRotatef(-doorAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(1.75f, 0.0f, 0.0f);
    glTranslatef(1.3f, 0.0f, 0.0f);
    glColor3f(0.8f, 0.7f, 0.3f); // Gold handle
    glutSolidSphere(0.15f, 10, 10);
    glPopMatrix();

    // Door panels decoration - outer side (rotate with door)
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(-1.75f, 0.0f, 0.0f);
        glRotatef(-doorAngle, 0.0f, 1.0f, 0.0f);
        glTranslatef(1.75f, 0.0f, 0.0f);
        glTranslatef(0.0f, -1.5f + i * 3.0f, -0.1f);
        glScalef(2.5f, 2.0f, 0.05f);
        drawCube(0.45f, 0.32f, 0.18f);
        glPopMatrix();
    }

    // Door panels decoration - inner side (lighter, visible when open)
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(-1.75f, 0.0f, 0.0f);
        glRotatef(-doorAngle, 0.0f, 1.0f, 0.0f);
        glTranslatef(1.75f, 0.0f, 0.0f);
        glTranslatef(0.0f, -1.5f + i * 3.0f, -0.35f);
        glScalef(2.5f, 2.0f, 0.05f);
        drawCube(0.55f, 0.45f, 0.3f);
        glPopMatrix();
    }

    glPopMatrix();
}


void drawWindow() {
    glPushMatrix();
    glTranslatef(12.2f, 6.0f, 0.0f); // Right wall position
    glRotatef(-90, 0.0f, 1.0f, 0.0f); // Rotate to face inward

    // --- EXISTING WINDOW FRAME (Unchanged) ---
    glColor3f(0.6f, 0.6f, 0.65f); // Silver Frame
    // Left
    glPushMatrix(); glTranslatef(-3.1f, 0.0f, 0.0f); glScalef(0.08f, 5.0f, 0.15f); glutSolidCube(1.0f); glPopMatrix();
    // Right
    glPushMatrix(); glTranslatef(3.1f, 0.0f, 0.0f); glScalef(0.08f, 5.0f, 0.15f); glutSolidCube(1.0f); glPopMatrix();
    // Top
    glPushMatrix(); glTranslatef(0.0f, 2.45f, 0.0f); glScalef(6.3f, 0.08f, 0.15f); glutSolidCube(1.0f); glPopMatrix();
    // Bottom
    glPushMatrix(); glTranslatef(0.0f, -2.45f, 0.0f); glScalef(6.3f, 0.08f, 0.15f); glutSolidCube(1.0f); glPopMatrix();

    // Glass Panes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float slideOffset = (windowAngle / 45.0f) * 3.0f;
    // Fixed Pane
    glPushMatrix(); glTranslatef(-1.55f, 0.0f, 0.05f); glColor4f(0.7f, 0.85f, 0.95f, 0.3f);
    glBegin(GL_QUADS); glVertex3f(-1.5f, -2.4f, 0.0f); glVertex3f(1.5f, -2.4f, 0.0f); glVertex3f(1.5f, 2.4f, 0.0f); glVertex3f(-1.5f, 2.4f, 0.0f); glEnd(); glPopMatrix();
    // Sliding Pane
    glPushMatrix(); glTranslatef(1.55f - slideOffset, 0.0f, 0.1f); glColor4f(0.7f, 0.85f, 0.95f, 0.3f);
    glBegin(GL_QUADS); glVertex3f(-1.5f, -2.4f, 0.0f); glVertex3f(1.5f, -2.4f, 0.0f); glVertex3f(1.5f, 2.4f, 0.0f); glVertex3f(-1.5f, 2.4f, 0.0f); glEnd(); glPopMatrix();
    glDisable(GL_BLEND);

    glPopMatrix();
}

void drawBed3D() {
    glPushMatrix();
    glTranslatef(-8.5f, 0.0f, -7.0f); // Moved left and toward back wall

    // Bed frame base (wood)
    glPushMatrix();
    glScalef(5.0f, 1.5f, 7.0f);
    drawCube(0.4f, 0.25f, 0.1f);
    glPopMatrix();

    // Bed legs (4 corners)
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
            glTranslatef(i * 2.3f, -0.5f, j * 3.3f);
            glScalef(0.3f, 0.5f, 0.3f);
            drawCube(0.35f, 0.2f, 0.08f);
            glPopMatrix();
        }
    }

    // Mattress (peach)
    glPushMatrix();
    glTranslatef(0.0f, 0.9f, 0.0f);
    glScalef(4.8f, 0.6f, 6.8f);
    drawCube(1.0f, 0.8f, 0.6f);
    glPopMatrix();

    // Mattress border (darker blue trim)
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.0f);
    glScalef(4.9f, 0.2f, 6.9f);
    drawCube(0.15f, 0.3f, 0.6f);
    glPopMatrix();

    // Pillow 1
    glPushMatrix();
    glTranslatef(-1.0f, 1.4f, -2.8f);
    glColor3f(1.0f, 0.8f, 0.6f);
    glScalef(1.6f, 0.35f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Pillow 2
    glPushMatrix();
    glTranslatef(1.0f, 1.4f, -2.8f);
    glColor3f(1.0f, 0.8f, 0.6f);
    glScalef(1.6f, 0.35f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Blanket (folded at foot of bed)
    glPushMatrix();
    glTranslatef(0.0f, 1.3f, 2.5f);
    glScalef(4.5f, 0.3f, 1.5f);
    drawCube(0.6f, 0.3f, 0.5f);
    glPopMatrix();

    // Headboard (wooden)
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, -3.5f);
    glScalef(5.0f, 2.5f, 0.3f);
    drawCube(0.45f, 0.3f, 0.15f);
    glPopMatrix();

    // Headboard decorative top
    glPushMatrix();
    glTranslatef(0.0f, 3.7f, -3.5f);
    glScalef(5.2f, 0.3f, 0.35f);
    drawCube(0.5f, 0.35f, 0.2f);
    glPopMatrix();

    glPopMatrix();
}

void drawWardrobe() {
    glPushMatrix();
    glTranslatef(9.0f, 3.5f, 10.0f); // Near front wall, close to sofa
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); // Rotate -90 degrees around Y-axis

    // Main wardrobe body (tall cabinet)
    glPushMatrix();
    glScalef(4.0f, 7.0f, 2.0f);
    drawCube(0.5f, 0.35f, 0.2f); // Brown wood
    glPopMatrix();

    // Left door
    glPushMatrix();
    glTranslatef(-1.0f, 0.0f, 1.05f);
    glScalef(1.8f, 6.5f, 0.1f);
    drawCube(0.55f, 0.4f, 0.25f); // Lighter brown
    glPopMatrix();

    // Right door
    glPushMatrix();
    glTranslatef(1.0f, 0.0f, 1.05f);
    glScalef(1.8f, 6.5f, 0.1f);
    drawCube(0.55f, 0.4f, 0.25f);
    glPopMatrix();

    // Door handles (gold)
    glPushMatrix();
    glTranslatef(-0.5f, 0.0f, 1.15f);
    glColor3f(0.8f, 0.7f, 0.2f);
    glutSolidSphere(0.1f, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, 0.0f, 1.15f);
    glColor3f(0.8f, 0.7f, 0.2f);
    glutSolidSphere(0.1f, 10, 10);
    glPopMatrix();

    // Top shelf/crown
    glPushMatrix();
    glTranslatef(0.0f, 3.6f, 0.0f);
    glScalef(4.2f, 0.3f, 2.2f);
    drawCube(0.45f, 0.3f, 0.15f);
    glPopMatrix();

    // Base/feet
    glPushMatrix();
    glTranslatef(0.0f, -3.6f, 0.0f);
    glScalef(4.1f, 0.4f, 2.1f);
    drawCube(0.4f, 0.25f, 0.1f);
    glPopMatrix();

    glPopMatrix();
}

void drawTableAndPC3D() {
    glPushMatrix();
    glTranslatef(5.0f, 1.5f, -6.0f); // Position Table (aligned with bed)

    // Table Top
    glPushMatrix();
    glScalef(5.0f, 0.2f, 3.0f);
    drawCube(0.4f, 0.2f, 0.0f);
    glPopMatrix();
    // Legs
    float legX = 2.2f, legZ = 1.2f;
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
            glTranslatef(i * legX, -1.0f, j * legZ);
            glScalef(0.2f, 2.0f, 0.2f);
            drawCube(0.3f, 0.15f, 0.0f);
            glPopMatrix();
        }
    }
    // Monitor (Enhanced realistic design)
    glPushMatrix();
    glTranslatef(-0.5f, 1.0f, -0.5f);

    // Monitor bezel (frame)
    glPushMatrix();
    glScalef(2.1f, 1.5f, 0.15f);
    drawCube(0.1f, 0.1f, 0.1f); // Black bezel
    glPopMatrix();

    // Monitor screen
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.08f);
    glScalef(1.95f, 1.35f, 0.05f);
    if (isPCOn) {
        // Screen on - blue background
        drawCube(0.15f, 0.4f, 0.7f);

        // Draw Windows logo (4 colored squares)
        glDisable(GL_LIGHTING);

        // Top-left square (red)
        glPushMatrix();
        glTranslatef(-0.15f, 0.12f, 0.55f);
        glScalef(0.25f, 0.25f, 0.01f);
        glColor3f(0.96f, 0.26f, 0.21f); // Red
        glutSolidCube(1.0f);
        glPopMatrix();

        // Top-right square (green)
        glPushMatrix();
        glTranslatef(0.15f, 0.12f, 0.55f);
        glScalef(0.25f, 0.25f, 0.01f);
        glColor3f(0.46f, 0.72f, 0.0f); // Green
        glutSolidCube(1.0f);
        glPopMatrix();

        // Bottom-left square (blue)
        glPushMatrix();
        glTranslatef(-0.15f, -0.12f, 0.55f);
        glScalef(0.25f, 0.25f, 0.01f);
        glColor3f(0.0f, 0.45f, 0.85f); // Blue
        glutSolidCube(1.0f);
        glPopMatrix();

        // Bottom-right square (yellow)
        glPushMatrix();
        glTranslatef(0.15f, -0.12f, 0.55f);
        glScalef(0.25f, 0.25f, 0.01f);
        glColor3f(1.0f, 0.73f, 0.0f); // Yellow
        glutSolidCube(1.0f);
        glPopMatrix();

        glEnable(GL_LIGHTING);
    }
    else {
        // Screen off - black
        drawCube(0.0f, 0.0f, 0.0f);
    }
    glPopMatrix();

    // Monitor stand base
    glPushMatrix();
    glTranslatef(0.0f, -0.85f, 0.0f);
    glScalef(0.8f, 0.1f, 0.6f);
    drawCube(0.15f, 0.15f, 0.15f);
    glPopMatrix();

    // Monitor stand neck
    glPushMatrix();
    glTranslatef(0.0f, -0.6f, 0.0f);
    glScalef(0.15f, 0.4f, 0.15f);
    drawCube(0.2f, 0.2f, 0.2f);
    glPopMatrix();

    glPopMatrix();

    // Tower (Enhanced)
    glPushMatrix();
    glTranslatef(1.8f, 0.6f, -0.5f);

    // Main tower body
    glPushMatrix();
    glScalef(0.8f, 1.5f, 1.5f);
    drawCube(0.1f, 0.1f, 0.1f);
    glPopMatrix();

    // Power LED (top front)
    if (isPCOn) {
        glDisable(GL_LIGHTING);
        glPushMatrix();
        glTranslatef(0.42f, 0.6f, 0.78f);
        glColor3f(0.0f, 1.0f, 0.0f); // Green LED
        glutSolidSphere(0.08f, 10, 10);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    }

    // Front panel details
    glPushMatrix();
    glTranslatef(0.42f, 0.0f, 0.5f);
    glScalef(0.02f, 0.8f, 1.0f);
    drawCube(0.15f, 0.15f, 0.15f);
    glPopMatrix();

    glPopMatrix();

    // Chair (facing the table) - Enhanced design
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 2.5f); // In front of table
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // Rotate 180 degrees to face table

    // Seat cushion with padding effect
    glPushMatrix();
    glTranslatef(0.0f, 0.55f, 0.0f);
    glScalef(1.6f, 0.25f, 1.6f);
    drawCube(0.45f, 0.3f, 0.2f); // Lighter wood with cushion
    glPopMatrix();

    // Seat padding top (softer appearance)
    glPushMatrix();
    glTranslatef(0.0f, 0.68f, 0.0f);
    glScalef(1.5f, 0.08f, 1.5f);
    drawCube(0.5f, 0.35f, 0.25f);
    glPopMatrix();

    // Seat frame base
    glPushMatrix();
    glTranslatef(0.0f, 0.35f, 0.0f);
    glScalef(1.7f, 0.15f, 1.7f);
    drawCube(0.35f, 0.2f, 0.1f);
    glPopMatrix();

    // Curved backrest (main panel)
    glPushMatrix();
    glTranslatef(0.0f, 1.4f, -0.7f);
    glScalef(1.6f, 1.8f, 0.25f);
    drawCube(0.4f, 0.25f, 0.15f); // Darker wood
    glPopMatrix();

    // Backrest cushion padding
    glPushMatrix();
    glTranslatef(0.0f, 1.4f, -0.55f);
    glScalef(1.4f, 1.5f, 0.15f);
    drawCube(0.5f, 0.35f, 0.25f); // Lighter cushion color
    glPopMatrix();

    // Backrest top rail (decorative)
    glPushMatrix();
    glTranslatef(0.0f, 2.35f, -0.7f);
    glScalef(1.7f, 0.2f, 0.3f);
    drawCube(0.45f, 0.3f, 0.15f);
    glPopMatrix();

    // Chair legs (rounded with tapered design)
    float chairLegPos[4][2] = { {0.7f, 0.7f}, {-0.7f, 0.7f}, {0.7f, -0.7f}, {-0.7f, -0.7f} };
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(chairLegPos[i][0], 0.0f, chairLegPos[i][1]);

        // Lower leg part
        glPushMatrix();
        glTranslatef(0.0f, -0.25f, 0.0f);
        glScalef(0.18f, 0.5f, 0.18f);
        drawCube(0.35f, 0.2f, 0.08f);
        glPopMatrix();

        // Upper leg part (slightly thicker)
        glPushMatrix();
        glTranslatef(0.0f, 0.15f, 0.0f);
        glScalef(0.2f, 0.3f, 0.2f);
        drawCube(0.35f, 0.2f, 0.08f);
        glPopMatrix();

        // Leg cap (decorative)
        glPushMatrix();
        glTranslatef(0.0f, -0.5f, 0.0f);
        glColor3f(0.3f, 0.15f, 0.05f);
        glutSolidSphere(0.12f, 8, 8);
        glPopMatrix();

        glPopMatrix();
    }

    // Backrest support legs (2 back corners - stylish)
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(chairLegPos[i][0], 1.1f, -0.7f);
        glScalef(0.18f, 1.2f, 0.18f);
        drawCube(0.35f, 0.2f, 0.08f);
        glPopMatrix();
    }

    // Armrests (optional - adds comfort)
    for (int side = -1; side <= 1; side += 2) {
        glPushMatrix();
        glTranslatef(side * 0.85f, 0.9f, 0.0f);
        glScalef(0.2f, 0.15f, 1.2f);
        drawCube(0.4f, 0.25f, 0.12f);
        glPopMatrix();

        // Armrest supports
        glPushMatrix();
        glTranslatef(side * 0.85f, 0.6f, 0.5f);
        glScalef(0.15f, 0.6f, 0.15f);
        drawCube(0.35f, 0.2f, 0.08f);
        glPopMatrix();
    }

    // Cross support bar (under seat for stability)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(1.4f, 0.1f, 0.1f);
    drawCube(0.32f, 0.18f, 0.06f);
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();
}

void drawNightstand() {
    glPushMatrix();
    glTranslatef(-4.5f, 0.5f, -7.5f); // Beside the bed (moved toward back wall)

    // Main cabinet body
    glPushMatrix();
    glScalef(1.5f, 1.8f, 1.2f);
    drawCube(0.4f, 0.25f, 0.15f); // Wood color
    glPopMatrix();

    // Top surface (slightly larger)
    glPushMatrix();
    glTranslatef(0.0f, 0.95f, 0.0f);
    glScalef(1.6f, 0.1f, 1.3f);
    drawCube(0.38f, 0.24f, 0.14f);
    glPopMatrix();

    // Drawer 1 (top)
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.65f);
    glScalef(1.3f, 0.6f, 0.05f);
    drawCube(0.35f, 0.22f, 0.13f);
    glPopMatrix();

    // Drawer 2 (bottom)
    glPushMatrix();
    glTranslatef(0.0f, -0.3f, 0.65f);
    glScalef(1.3f, 0.6f, 0.05f);
    drawCube(0.35f, 0.22f, 0.13f);
    glPopMatrix();

    // Drawer handles
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.7f);
    glColor3f(0.7f, 0.6f, 0.3f); // Gold
    glutSolidSphere(0.08f, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -0.3f, 0.7f);
    glColor3f(0.7f, 0.6f, 0.3f);
    glutSolidSphere(0.08f, 10, 10);
    glPopMatrix();

    glPopMatrix();
}

void drawLamp3D() {
    glPushMatrix();
    glTranslatef(-4.5f, 1.5f, -7.5f); // On top of nightstand (moved toward back wall)

    // Lamp base
    glPushMatrix();
    glScalef(0.4f, 0.1f, 0.4f);
    drawCube(0.3f, 0.3f, 0.3f);
    glPopMatrix();

    // Lamp stem
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.0f);
    glScalef(0.1f, 1.2f, 0.1f);
    drawCube(0.6f, 0.6f, 0.6f);
    glPopMatrix();

    // Lamp shade
    glPushMatrix();
    glTranslatef(0.0f, 1.3f, 0.0f);
    glRotatef(-90, 1, 0, 0);
    glColor3f(0.9f, 0.8f, 0.6f); // Cream shade
    glutSolidCone(0.5, 0.6, 15, 15);
    glPopMatrix();

    if (isLampOn) {
        GLfloat lightPos[] = { -4.5f, 3.0f, -7.5f, 1.0f };
        GLfloat lightColor[] = { 1.0f, 0.95f, 0.7f, 1.0f };
        glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor);
        glEnable(GL_LIGHT1);
    }
    else {
        glDisable(GL_LIGHT1);
    }
    glPopMatrix();
}

void drawSofa() {
    glPushMatrix();
    glTranslatef(9.0f, 0.5f, 3.0f); // Near the window, moved toward front wall
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f); // Rotate 270 degrees (or -90) to face right

    // Sofa base/seat
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f);
    glScalef(5.0f, 0.6f, 2.0f);
    drawCube(0.85f, 0.55f, 0.25f); // Caramel color
    glPopMatrix();

    // Seat cushions (3 sections)
    for (int i = -1; i <= 1; i++) {
        glPushMatrix();
        glTranslatef(i * 1.5f, 0.8f, 0.0f);
        glScalef(1.3f, 0.3f, 1.8f);
        drawCube(0.8f, 0.6f, 0.4f); // Clay color
        glPopMatrix();
    }

    // Backrest
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, -0.9f);
    glScalef(5.0f, 1.8f, 0.4f);
    drawCube(0.3f, 0.2f, 0.5f);
    glPopMatrix();

    // Back cushions (3 sections)
    for (int i = -1; i <= 1; i++) {
        glPushMatrix();
        glTranslatef(i * 1.5f, 1.5f, -0.65f);
        glScalef(1.3f, 1.5f, 0.25f);
        drawCube(0.8f, 0.6f, 0.4f); // Clay color
        glPopMatrix();
    }

    // Left armrest
    glPushMatrix();
    glTranslatef(-2.7f, 0.8f, 0.0f);
    glScalef(0.6f, 1.0f, 2.0f);
    drawCube(0.28f, 0.18f, 0.45f);
    glPopMatrix();

    // Right armrest
    glPushMatrix();
    glTranslatef(2.7f, 0.8f, 0.0f);
    glScalef(0.6f, 1.0f, 2.0f);
    drawCube(0.28f, 0.18f, 0.45f);
    glPopMatrix();

    // Armrest tops (padded)
    for (int side = -1; side <= 1; side += 2) {
        glPushMatrix();
        glTranslatef(side * 2.7f, 1.3f, 0.0f);
        glScalef(0.55f, 0.2f, 1.9f);
        drawCube(0.35f, 0.25f, 0.55f);
        glPopMatrix();
    }

    // Sofa legs (6 wooden legs)
    float sofaLegPos[6][2] = { {-2.3f, 0.8f}, {0.0f, 0.8f}, {2.3f, 0.8f},
                               {-2.3f, -0.8f}, {0.0f, -0.8f}, {2.3f, -0.8f} };
    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        glTranslatef(sofaLegPos[i][0], -0.3f, sofaLegPos[i][1]);
        glScalef(0.2f, 0.4f, 0.2f);
        drawCube(0.25f, 0.15f, 0.08f); // Dark wood
        glPopMatrix();
    }

    // Decorative throw pillows
    // Pillow 1 (left)
    glPushMatrix();
    glTranslatef(-1.5f, 1.2f, 0.2f);
    glRotatef(15, 0, 0, 1);
    glScalef(0.7f, 0.7f, 0.3f);
    drawCube(0.8f, 0.4f, 0.2f); // Orange pillow
    glPopMatrix();

    // Pillow 2 (right)
    glPushMatrix();
    glTranslatef(1.5f, 1.2f, 0.2f);
    glRotatef(-15, 0, 0, 1);
    glScalef(0.7f, 0.7f, 0.3f);
    drawCube(0.9f, 0.8f, 0.2f); // Yellow pillow
    glPopMatrix();

    glPopMatrix();
}

void drawCoffeeTable() {
    glPushMatrix();
    glTranslatef(7.0f, 0.0f, 3.0f); // Moved towards TV (left on X axis) and forward on Z
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f); // Match sofa rotation

    // Table top (wooden surface)
    glPushMatrix();
    glTranslatef(0.0f, 1.2f, 0.0f);
    glScalef(4.0f, 0.15f, 1.5f);
    drawCube(0.6f, 0.4f, 0.2f); // Wood brown color
    glPopMatrix();

    // Table legs (4 legs at corners)
    float legOffsets[4][2] = {
        {-1.8f, -0.65f}, // Front-left
        {1.8f, -0.65f},  // Front-right
        {-1.8f, 0.65f},  // Back-left
        {1.8f, 0.65f}    // Back-right
    };

    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(legOffsets[i][0], 0.6f, legOffsets[i][1]);
        glScalef(0.25f, 1.2f, 0.25f);
        drawCube(0.5f, 0.3f, 0.15f); // Darker wood
        glPopMatrix();
    }

    // Decorative items on table top (optional)
    // Magazine/book stack
    glPushMatrix();
    glTranslatef(-1.0f, 1.35f, 0.0f);
    glScalef(0.8f, 0.1f, 0.5f);
    drawCube(0.8f, 0.6f, 0.4f); // Magazine color
    glPopMatrix();

    // Potted plant
    glPushMatrix();
    glTranslatef(1.2f, 1.35f, 0.0f);
    glColor3f(0.6f, 0.3f, 0.1f); // Pot color
    glutSolidCone(0.3f, 0.4f, 16, 16);
    glPopMatrix();

    // Plant leaves (simplified)
    glPushMatrix();
    glTranslatef(1.2f, 1.9f, 0.0f);
    glScalef(0.4f, 0.4f, 0.4f);
    glColor3f(0.2f, 0.7f, 0.2f);
    glutSolidSphere(1.0f, 16, 16);
    glPopMatrix();

    glPopMatrix();
}

void drawTV() {
    glPushMatrix();
    glTranslatef(-11.8f, 6.0f, 3.0f); // Left wall, opposite sofa
    glRotatef(90, 0.0f, 1.0f, 0.0f); // Face toward sofa

    // TV Frame (thin bezel modern design)
    glPushMatrix();
    glScalef(5.0f, 3.0f, 0.15f);
    drawCube(0.05f, 0.05f, 0.05f); // Black frame
    glPopMatrix();

    // TV Screen
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.1f);
    glScalef(4.8f, 2.8f, 0.05f);

    if (isTVOn) {
        // Different background colors based on channel
        float r, g, b;
        switch (tvChannel) {
        case 1: // Blue theme
            r = 0.1f + 0.1f * sin(tvAnimTime * 2.0f);
            g = 0.2f + 0.2f * sin(tvAnimTime * 1.5f + 1.0f);
            b = 0.5f + 0.3f * sin(tvAnimTime * 1.8f + 2.0f);
            break;
        case 2: // Red/Orange theme
            r = 0.6f + 0.3f * sin(tvAnimTime * 2.0f);
            g = 0.2f + 0.2f * sin(tvAnimTime * 1.5f);
            b = 0.1f + 0.1f * sin(tvAnimTime * 1.8f);
            break;
        case 3: // Green nature theme
            r = 0.1f + 0.1f * sin(tvAnimTime * 1.5f);
            g = 0.5f + 0.3f * sin(tvAnimTime * 2.0f);
            b = 0.2f + 0.2f * sin(tvAnimTime * 1.8f);
            break;
        case 4: // Purple/Pink theme
            r = 0.5f + 0.3f * sin(tvAnimTime * 1.8f);
            g = 0.1f + 0.1f * sin(tvAnimTime * 2.0f);
            b = 0.6f + 0.3f * sin(tvAnimTime * 1.5f);
            break;
        case 5: // Rainbow cycling
            r = 0.5f + 0.5f * sin(tvAnimTime * 0.5f);
            g = 0.5f + 0.5f * sin(tvAnimTime * 0.5f + 2.09f);
            b = 0.5f + 0.5f * sin(tvAnimTime * 0.5f + 4.18f);
            break;
        default:
            r = 0.3f; g = 0.3f; b = 0.3f;
        }
        drawCube(r, g, b);
    }
    else {
        drawCube(0.02f, 0.02f, 0.02f); // Off - dark screen
    }
    glPopMatrix();

    // Animated patterns on screen when TV is on
    if (isTVOn) {
        glDisable(GL_LIGHTING);

        switch (tvChannel) {
        case 1: // Channel 1: Rainbow horizontal bars
            for (int i = 0; i < 5; i++) {
                glPushMatrix();
                float yOffset = sin(tvAnimTime * 3.0f + i * 0.8f) * 1.0f;
                glTranslatef(0.0f, yOffset, 0.15f);
                glScalef(4.5f, 0.15f, 0.01f);
                float hue = fmod(tvAnimTime * 0.5f + i * 0.2f, 1.0f);
                float hr = sin(hue * 6.28f) * 0.5f + 0.5f;
                float hg = sin(hue * 6.28f + 2.09f) * 0.5f + 0.5f;
                float hb = sin(hue * 6.28f + 4.18f) * 0.5f + 0.5f;
                glColor3f(hr, hg, hb);
                glutSolidCube(1.0f);
                glPopMatrix();
            }
            break;

        case 2: // Channel 2: Bouncing circles
            for (int i = 0; i < 8; i++) {
                glPushMatrix();
                float xPos = sin(tvAnimTime * 2.0f + i * 0.785f) * 1.8f;
                float yPos = cos(tvAnimTime * 1.5f + i * 0.785f) * 1.0f;
                glTranslatef(xPos, yPos, 0.16f);
                float hue = fmod(tvAnimTime * 0.3f + i * 0.125f, 1.0f);
                float cr = sin(hue * 6.28f) * 0.5f + 0.5f;
                float cg = sin(hue * 6.28f + 2.09f) * 0.5f + 0.5f;
                float cb = sin(hue * 6.28f + 4.18f) * 0.5f + 0.5f;
                glColor3f(cr, cg, cb);
                glutSolidSphere(0.25f, 12, 12);
                glPopMatrix();
            }
            break;

        case 3: // Channel 3: Matrix-style falling bars
            for (int i = 0; i < 10; i++) {
                glPushMatrix();
                float xOffset = -2.0f + i * 0.45f;
                float yFall = fmod(tvAnimTime * 2.0f + i * 0.7f, 3.0f) - 1.5f;
                glTranslatef(xOffset, yFall, 0.15f);
                glScalef(0.12f, 0.8f, 0.01f);
                float intensity = 0.3f + 0.7f * (1.0f - fabs(yFall) / 1.5f);
                glColor3f(0.0f, intensity, 0.0f);
                glutSolidCube(1.0f);
                glPopMatrix();
            }
            break;

        case 4: // Channel 4: Pulsing concentric rings
            for (int i = 0; i < 5; i++) {
                glPushMatrix();
                glTranslatef(0.0f, 0.0f, 0.15f);
                float scale = 0.3f + i * 0.4f + 0.2f * sin(tvAnimTime * 3.0f - i * 0.5f);
                glScalef(scale, scale * 0.6f, 0.01f);
                float hue = fmod(tvAnimTime * 0.2f + i * 0.15f, 1.0f);
                glColor3f(0.8f * hue, 0.2f, 1.0f - hue * 0.5f);
                glutWireTorus(0.05f, 1.0f, 8, 20);
                glPopMatrix();
            }
            break;

        case 5: // Channel 5: Spinning star pattern
            for (int i = 0; i < 12; i++) {
                glPushMatrix();
                float rotAngle = tvAnimTime * 50.0f + i * 30.0f;
                float dist = 0.8f + 0.3f * sin(tvAnimTime * 2.0f + i);
                float xPos = cos(rotAngle * 0.0174533f) * dist;
                float yPos = sin(rotAngle * 0.0174533f) * dist * 0.6f;
                glTranslatef(xPos, yPos, 0.16f);
                glRotatef(rotAngle * 2.0f, 0.0f, 0.0f, 1.0f);
                float hue = fmod(i / 12.0f + tvAnimTime * 0.1f, 1.0f);
                glColor3f(1.0f, hue, 1.0f - hue);
                glutSolidCube(0.15f);
                glPopMatrix();
            }
            // Central spinning element
            glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.17f);
            glRotatef(tvAnimTime * 100.0f, 0.0f, 0.0f, 1.0f);
            glColor3f(1.0f, 1.0f, 0.0f);
            glutSolidSphere(0.2f, 10, 10);
            glPopMatrix();
            break;
        }

        glEnable(GL_LIGHTING);
    }

    // Channel number display when TV is on
    if (isTVOn) {
        glPushMatrix();
        glTranslatef(1.8f, 1.1f, 0.18f);
        glDisable(GL_LIGHTING);
        glColor3f(1.0f, 1.0f, 1.0f);
        glScalef(0.003f, 0.003f, 0.001f);
        char channelStr[10];
        sprintf(channelStr, "CH %d", tvChannel);
        for (int i = 0; channelStr[i] != '\0'; i++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, channelStr[i]);
        }
        glEnable(GL_LIGHTING);
        glPopMatrix();
    }

    // TV Stand/Mount (wall bracket)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.2f);
    glScalef(0.8f, 0.5f, 0.3f);
    drawCube(0.15f, 0.15f, 0.15f);
    glPopMatrix();

    // Power LED indicator
    glPushMatrix();
    glTranslatef(0.0f, -1.4f, 0.1f);
    glDisable(GL_LIGHTING);
    if (isTVOn) {
        glColor3f(0.0f, 1.0f, 0.0f); // Green when on
    }
    else {
        glColor3f(1.0f, 0.0f, 0.0f); // Red when off
    }
    glutSolidSphere(0.06f, 8, 8);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    glPopMatrix();
}

void drawRoof() {
    // Pitched roof on top of the room - house-like appearance
    glPushMatrix();
    glTranslatef(0.0f, 13.0f, 0.0f); // Top of room

    // Main roof structure - two slanted panels forming a peak
    // Left roof panel (angled)


    // Roof overhang (eaves) - extends beyond walls
    // Front eave
    glPushMatrix();
    glTranslatef(0.0f, -0.3f, 13.5f);
    glScalef(27.0f, 0.5f, 2.0f);
    drawCube(0.5f, 0.4f, 0.2f);
    glPopMatrix();

    // Back eave
    glPushMatrix();
    glTranslatef(0.0f, -0.3f, -13.5f);
    glScalef(27.0f, 0.5f, 2.0f);
    drawCube(0.5f, 0.4f, 0.2f);
    glPopMatrix();

    glPopMatrix();
}

void drawFan3D() {
    glPushMatrix();
    glTranslatef(0.0f, 11.0f, 0.0f); // Higher Ceiling
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glutSolidCone(0.5, 1.0, 10, 10);
    glPopMatrix();
    glRotatef(fanAngle, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidSphere(0.5f, 20, 20);
    glColor3f(0.8f, 0.8f, 0.8f);
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glRotatef(i * 120, 0.0f, 1.0f, 0.0f);
        glTranslatef(3.0f, 0.0f, 0.0f); // Longer blades for bigger room
        glScalef(6.0f, 0.1f, 1.5f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }
    glPopMatrix();
}

void drawWallSconce() {
    // Wall sconce on the back wall, center-top, under LED strip
    glPushMatrix();
    glTranslatef(0.0f, 9.5f, -12.2f); // Back wall, center, under LED strip

    // Base plate (circular, mounted on wall)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.05f);
    glColor3f(0.3f, 0.3f, 0.3f); // Dark metal
    glRotatef(90, 0, 1, 0);
    glutSolidCone(0.6f, 0.1f, 20, 20);
    glPopMatrix();

    // Decorative sconce cover (curved shade)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.2f);

    // Outer decorative shell - semi-circular
    glColor3f(0.85f, 0.75f, 0.6f); // Cream/beige color
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(0.55f, 0.8f, 25, 25);
    glPopMatrix();

    // Inner reflector (shiny metallic)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.15f);
    glColor3f(0.9f, 0.85f, 0.7f); // Brushed metal/gold
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(0.45f, 0.5f, 20, 20);
    glPopMatrix();

    // Light bulb inside
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.3f);
    glColor3f(1.0f, 1.0f, 0.8f); // Warm bulb color
    glutSolidSphere(0.15f, 15, 15);
    glPopMatrix();

    // Decorative rim/trim
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.05f);
    glColor3f(0.5f, 0.4f, 0.2f); // Bronze/brass
    glRotatef(-90, 1, 0, 0);
    glutWireCone(0.62f, 0.15f, 20, 20);
    glPopMatrix();

    glPopMatrix();

    // Add light source for sconce
    GLfloat sconcePos[] = { 0.0f, 9.5f, -12.0f, 1.0f };
    GLfloat sconceColor[] = { 1.0f, 0.95f, 0.85f, 1.0f };
    glLightfv(GL_LIGHT3, GL_POSITION, sconcePos);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, sconceColor);
    glEnable(GL_LIGHT3);
}

void drawText() {

    glPushMatrix();
    glTranslatef(-7.0f, 6.5f, 14.0f); // Position above door, slightly left
    glScalef(0.005f, 0.005f, 0.005f); // Smaller scale
    glColor3f(1.0f, 1.0f, 1.0f); // White color

    // Use stroke font to render text
    const char* text = "";
    for (const char* c = text; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *c);
    }

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(camX, 5.0f, camZ,
        camX + lx, 5.0f, camZ + lz,
        0.0f, 1.0f, 0.0f);

    // Day/Night Logic
    if (isNight) {
        glClearColor(0.05f, 0.05f, 0.1f, 1.0f); // Night Sky Color
        glDisable(GL_LIGHT0); // Turn off Sun
    }
    else {
        glClearColor(0.5f, 0.8f, 0.9f, 1.0f); // Day Sky Color
        glEnable(GL_LIGHT0); // Turn on Sun
    }

    drawRoom();
    drawLEDStrip(); // LED light strip on back wall
    drawDoor(); // Door on front wall (camera side)
    drawWindow(); // Window on back wall (opposite side)
    drawWallSconce(); // Wall sconce on back wall
 
    drawBed3D();
    drawWardrobe(); // Wardrobe in front of bed
    drawNightstand(); // Side cabinet beside bed
    drawTableAndPC3D();
    drawLamp3D(); // Table lamp on nightstand
    drawFan3D();
    // drawDressingTable(); // Dressing table with mirror and ornaments
    // drawDressingTableChair(); // Chair for dressing table
    drawBookshelf();
    drawSofa(); // Sofa near the window
    drawCoffeeTable(); // Coffee table in front of sofa
    drawTV(); // LED TV on left wall opposite sofa
    drawText(); // Draw text in front of door

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void update(int value) {
    if (isFanOn) {
        fanAngle += 5.0f;
        if (fanAngle > 360) fanAngle -= 360;
    }

    // Smooth door opening/closing animation
    if (isDoorOpen && doorAngle < 90.0f) {
        doorAngle += 3.0f;
        if (doorAngle > 90.0f) doorAngle = 90.0f;
    }
    else if (!isDoorOpen && doorAngle > 0.0f) {
        doorAngle -= 3.0f;
        if (doorAngle < 0.0f) doorAngle = 0.0f;
    }

    // Smooth window opening/closing animation
    if (isWindowOpen && windowAngle < 45.0f) {
        windowAngle += 2.0f;
        if (windowAngle > 45.0f) windowAngle = 45.0f;
    }
    else if (!isWindowOpen && windowAngle > 0.0f) {
        windowAngle -= 2.0f;
        if (windowAngle < 0.0f) windowAngle = 0.0f;
    }

    // TV animation timer
    if (isTVOn) {
        tvAnimTime += 0.05f;
        if (tvAnimTime > 628.0f) tvAnimTime = 0.0f; // Reset after ~100 cycles
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'f': case 'F': isFanOn = !isFanOn; break;
    case 'l': case 'L': isLampOn = !isLampOn; isLEDOn = !isLEDOn; break;
    case 'p': case 'P': isPCOn = !isPCOn; break;
    case 'n': case 'N': isNight = !isNight; break; // Toggle Night
    case 'd': case 'D': isDoorOpen = !isDoorOpen; break; // Toggle Door
    case 'w': case 'W': isWindowOpen = !isWindowOpen; break; // Toggle Window
    case 't': case 'T': isTVOn = !isTVOn; break; // Toggle T
        if (isTVOn) {
            tvChannel++;
            if (tvChannel > MAX_CHANNELS) tvChannel = 1;
        }
        break;
    case '[': // Previous photo
        if (!photoList.empty()) {
            currentPhotoIndex--;
            if (currentPhotoIndex < 0) currentPhotoIndex = photoList.size() - 1;

            std::string photoPath = photoList[currentPhotoIndex];
            if (photoPath.find(".jpg") != std::string::npos ||
                photoPath.find(".jpeg") != std::string::npos ||
                photoPath.find(".JPG") != std::string::npos ||
                photoPath.find(".JPEG") != std::string::npos) {
                photoFrameTexture = loadJPGTexture(photoPath.c_str());
            }
            else {
                photoFrameTexture = loadBMPTexture(photoPath.c_str());
            }
        }
        break;
    case ']': // Next photo
        if (!photoList.empty()) {
            currentPhotoIndex++;
            if (currentPhotoIndex >= photoList.size()) currentPhotoIndex = 0;

            std::string photoPath = photoList[currentPhotoIndex];
            if (photoPath.find(".jpg") != std::string::npos ||
                photoPath.find(".jpeg") != std::string::npos ||
                photoPath.find(".JPG") != std::string::npos ||
                photoPath.find(".JPEG") != std::string::npos) {
                photoFrameTexture = loadJPGTexture(photoPath.c_str());
            }
            else {
                photoFrameTexture = loadBMPTexture(photoPath.c_str());
            }
        }
        break;
    case 27: exit(0); break;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    float fraction = 1.0f; // Faster movement
    float angleFraction = 0.05f;
    switch (key) {
    case GLUT_KEY_LEFT:
        angle -= angleFraction;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case GLUT_KEY_RIGHT:
        angle += angleFraction;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case GLUT_KEY_UP:
        camX += lx * fraction;
        camZ += lz * fraction;
        break;
    case GLUT_KEY_DOWN:
        camX -= lx * fraction;
        camZ -= lz * fraction;
        break;
    }
    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

    // Load back wall texture from Image folder
    backWallTexture = loadBMPTexture("Image/wall_image.bmp");
    if (backWallTexture == 0) {
        std::cout << "Note: No texture found in Image folder." << std::endl;
    }

    // Load photos from album folder
    loadPhotosFromFolder("album");
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Dream Bedroom V2 - Bigger & Better");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
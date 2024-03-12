void kmain() {
    const char* msg = "Hello, kernel world!";
    // VGA text mode buffer starts at address 0xB8000
    char* video_memory = (char*) 0xB8000;
    // Attribute byte for our default color scheme (white on black)
    char attribute_byte = 0x0F; // White on black background
    // Write the message to the video memory
    for (int i = 0; msg[i] != '\0'; ++i) {
        video_memory[i * 2] = msg[i];
        video_memory[i * 2 + 1] = attribute_byte;
    }
}

// Use __attribute__((constructor)) as an alternative entry point
__attribute__((constructor)) void kernel_entry() {
    kmain();
}
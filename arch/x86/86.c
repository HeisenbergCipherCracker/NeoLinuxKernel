void x86_init() {
    // Initialize x86-specific hardware (e.g., PIC, PIT, etc.)
    init_pic();
    init_pit();
}
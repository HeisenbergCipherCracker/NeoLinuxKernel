/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
#ifndef VGA_H
#define VGA_H


#define VGA_WIDTH 320
#define VGA_HEIGHT 200

void vga_init();
void vga_set_palette_color(uint8_t palette_no, uint8_t r, uint8_t g, uint8_t b);
void vga_buffer_draw_pixel(uint8_t* buffer, int x, int y, uint8_t palette_no);
void vga_buffer_clear(uint8_t* buffer);
void vga_draw_buffer(const uint8_t* buffer);


#endif // !VGA_H
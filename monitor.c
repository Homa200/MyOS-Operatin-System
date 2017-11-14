#include <stdint.h>
 
 static inline void outb(short port, char val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline char inb(short port)
{
    char ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}
 
enum video_type
{
    VIDEO_TYPE_NONE = 0x00,
    VIDEO_TYPE_COLOUR = 0x20,
    VIDEO_TYPE_MONOCHROME = 0x30,
};
 
short detect_bios_area_hardware(void)
{
    const short* bda_detected_hardware_ptr = (const short*) 0x410;
    return *bda_detected_hardware_ptr;
}
 
enum video_type get_bios_area_video_type(void)
{
    return (enum video_type) (detect_bios_area_hardware() & 0x30);
}

 
void disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
} 

void ata_test()
{

outb(0x1F6, 0xA0); //Select drive

outb(0x1F2, 0); //SectorCount = 0
outb(0x1F3, 0); //LBAlo = 0
outb(0x1F4, 0); //LBAmid = 0
outb(0x1F5, 0); //LBAhi IO = 0

outb(0x1F7, 0xEC); //Send identify command


if(inb(0x1F7) == 0)
{
print("Device at [Channel 1] and [Master] not found\n"); 
}
else
{
print("Found Device at [Channel 1] and [Master]\n"); 
}
}


void crt_scroll(unsigned short lines) {
    unsigned short offset = lines * 2 * 80;
    asm("\n  mov $0xd, %%al"
        "\n  mov $0x3d4, %%dx"
        "\n  outb %%al, %%dx"
        "\n  inc %%dx"
        "\n  mov %w0, %%ax"
        "\n  outb %%al, %%dx"
        "\n  mov $0xc, %%al"
        "\n  mov $0x3d4, %%dx"
        "\n  outb %%al,%%dx"
        "\n  mov %%ah,%%al"
        "\n  inc %%dx"
        "\n  outb %%al, %%dx"
        "\n  "
            :              /* no output */
            :"m"(offset)   /* input */
            :"%ax","%dx"   /* clobbered register */
    );  
}



static struct {
	char dev_class, dev_subclass; //added dev_ to prevent errors in C++

} pci_device_type_strings[] = {
	{0x00, 0x00, "Unknown device"},
	{0x00, 0x01, "VGA-compatible Device"},
};

char * itoa( int value, char * str, int base )
{
    char * rc;
    char * ptr;
    char * low;
    // Check for supported base.
    if ( base < 2 || base > 36 )
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    // Set '-' for negative decimals.
    if ( value < 0 && base == 10 )
    {
        *ptr++ = '-';
    }
    // Remember where the numbers start.
    low = ptr;
    // The actual conversion.
    do
    {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while ( value );
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while ( low < ptr )
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

void ata_write()
{
	if(inb(0x8086) == 1)
{
print("Intel Corporation\n"); 
}
	if(inb(0x10DE) == 1)
{
print("NVIDIA\n"); 
}
else
{
print("Not found pci devices..\n"); 
}
}


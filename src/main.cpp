#include <gccore.h>
#include <wiiuse/wpad.h>
#include <ogc/system.h>
#include <stdio.h>
#include <stdlib.h>

static GXRModeObj *rmode;
static void *xfb;

int main(int argc, char **argv) {
    VIDEO_Init();
    WPAD_Init();

    rmode = VIDEO_GetPreferredMode(NULL);
    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

    console_init(
        xfb, 20, 20,
        rmode->fbWidth,
        rmode->xfbHeight,
        rmode->xfbHeight * VI_DISPLAY_PIX_SZ
    );

    VIDEO_Configure(rmode);
    VIDEO_SetNextFramebuffer(xfb);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();

    int vyber = 0;
    bool koniec = false;

    while (!koniec) {
        WPAD_ScanPads();
        u32 tlacidla = WPAD_ButtonsDown(0);

        if (tlacidla & WPAD_BUTTON_UP)
            vyber = (vyber + 2) % 3;

        if (tlacidla & WPAD_BUTTON_DOWN)
            vyber = (vyber + 1) % 3;

        if (tlacidla & WPAD_BUTTON_A) {
            if (vyber == 0) {
                printf("\x1b[2J\x1b[H");
                printf("NEKTARYNKY\n");
                printf("Escape from Henio 1\n");
                printf("Warehouse of Tesco\n\n");
                printf("Zbieraj 10 nektariniek a unikni Heniovi!\n");
                printf("\nStlac B pre navrat do menu.\n");

                while (true) {
                    WPAD_ScanPads();
                    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_B)
                        break;
                    VIDEO_WaitVSync();
                }
            }
            else if (vyber == 1) {
                printf("\x1b[2J\x1b[H");
                printf("NASTAVENIA\n");
                printf("Zatial sa pripravuju!\n");
                printf("\nStlac B pre navrat.\n");

                while (true) {
                    WPAD_ScanPads();
                    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_B)
                        break;
                    VIDEO_WaitVSync();
                }
            }
            else {
                koniec = true;
            }
        }

        if (tlacidla & WPAD_BUTTON_HOME)
            koniec = true;

        printf("\x1b[2J\x1b[H");
        printf("================================\n");
        printf(" NEKTARYNKY: ESCAPE FROM HENIO 1\n");
        printf("       WAREHOUSE OF TESCO\n");
        printf("================================\n\n");

        printf("%s HRAT\n", vyber == 0 ? ">" : " ");
        printf("%s NASTAVENIA\n", vyber == 1 ? ">" : " ");
        printf("%s UKONCIT\n", vyber == 2 ? ">" : " ");

        printf("\nOvládanie: sipky, A = potvrdit\n");

        VIDEO_WaitVSync();
    }

    return 0;
}

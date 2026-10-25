#include <switch.h>
int main(int argc, char* argv[]){
 consoleInit(NULL);
 printf("DOA1 Ultimate NX-PORT\n");
 printf("Folder DOA1, DOA2, Media ada di sebelah NRO\n");
 printf("Build Fix dari yang gagal kemarin\n");
 printf("Press + to exit\n");
 while(appletMainLoop()){
  hidScanInput();
  if(hidKeysDown(CONTROLLER_P1_AUTO) & KEY_PLUS) break;
  consoleUpdate(NULL);
 }
 consoleExit(NULL);
 return 0;
}

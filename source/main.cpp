#include <switch.h>
#include <stdio.h>

bool fileExists(const char* path){
 FILE* f=fopen(path,"rb");
 if(f){fclose(f);return true;}
 return false;
}
long getFileSize(const char* p){
 FILE* f=fopen(p,"rb");
 if(!f)return 0;
 fseek(f,0,SEEK_END);
 long s=ftell(f);
 fclose(f);
 return s;
}

int main(){
 consoleInit(NULL);
 PadState pad;
 padConfigureInput(1,HidNpadStyleSet_NpadStandard);
 padInitializeDefault(&pad);
 int sel=0;
 while(appletMainLoop()){
  padUpdate(&pad);
  u64 k=padGetButtonsDown(&pad);
  consoleClear();
  printf("\x1b[30;47m DOA1U NX PORT - BLACK NX STYLE \x1b[0m\n");
  printf("Based on SCDA-XBERecomp + BLACK-NX-PORT\n");
  printf("----------------------------------------\n\n");
  
  bool has_xbe = fileExists("sdmc:/doa1u/doa1.xbe") || fileExists("sdmc:/switch/DOA1U-NX-PORT/doa1.xbe");
  bool has_sfd = fileExists("sdmc:/doa1u/DOA1/ss_end.sfd");
  long sz = fileExists("sdmc:/doa1u/doa1.xbe") ? getFileSize("sdmc:/doa1u/doa1.xbe") : getFileSize("sdmc:/switch/DOA1U-NX-PORT/doa1.xbe");
  
  printf("[CHECK] Like BLACK-NX-PORT checks sdmc:/black/\n");
  printf(" %s doa1.xbe [%ld KB] ORIGINAL XBOX\n", has_xbe?"\x1b[32m[OK]\x1b[0m":"\x1b[31m[MISSING]\x1b[0m", sz/1024);
  printf(" %s DOA1/ss_end.sfd 21MB\n", has_sfd?"\x1b[32m[OK]\x1b[0m":"\x1b[33m[--]\x1b[0m");
  
  if(has_xbe){
   printf("\n\x1b[32;1m>> ASSETS FOUND <<\x1b[0m\n\n");
   printf(" %s START DOA1U\n", sel==0?"\x1b[33m>>\x1b[0m":"  ");
   printf(" %s EXIT\n", sel==1?"\x1b[33m>>\x1b[0m":"  ");
   printf("\nEngine: XBE Recomp -> deko3d\nLike BLACK-NX-PORT\n");
  }else{
   printf("\n\x1b[31mMISSING XBE\x1b[0m\nCopy: D:/MyNewGame/Dead or Alive 1 Ultimate/doa1.xbe\n -> sdmc:/doa1u/doa1.xbe\n\n");
   printf(" %s EXIT\n", sel==0?"\x1b[33m>>\x1b[0m":"  ");
  }
  
  if(k & HidNpadButton_AnyUp) sel--;
  if(k & HidNpadButton_AnyDown) sel++;
  if(sel<0) sel=1;
  if(sel>1) sel=0;
  if(k & HidNpadButton_A) if(sel==1) break;
  if(k & HidNpadButton_Plus) break;
  consoleUpdate(NULL);
 }
 consoleExit(NULL);
 return 0;
}

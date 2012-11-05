/******************* 
 *A program that draws the pixels onto the screen of the game. The program will increase the size of each box in the screen by SizeIncreaseX and SizeIncreaseY when called.
 * The program will resize the box to MINX AND MINY, when X, Y of the box reaches MAXX and MAXY.
 */
 
 #define MINY 20;
 #define MINX 10;
 #define MAXY 240;
 #define MAXX 360;
 #define SizeIncreaseX 10; 
 #define SizeIncreaseY 10;

struct Square SquareArray[10];
struct Pixel buffer[320][240];

struct Pixel {
	unsigned b:5;
	unsigned g:6;
	unsigned r:5;
}

struct Square{
	int width;
	int height;
	int center;
}

//creates the inital array of squares
struct Square * squareInit(){
//create sqaure and return the pointer to the start of the array of squares
	return array;
}

//write the buffer to the screen
void writeBufferToScreen(struct Pixel **buffer){
}

//clear the buffer
 void clearBuffer(struct Pixel **buffer){
}

//write the array to the buffer
void writeArrayToBuffer(struct Square *array){
}

//write one squaure to the buffer
 void writeSquareToBuffer(struct Square square, struct Pixel **buffer){
}

//loop thru the squares and adjust its size
 void adjustSize(struct Square *array){
 }
 
 extern void TimerHandler(){
	adjustSize();
	clearBuffer();
	writeArrayToBuffer();
	writeBufferToScreen(); 
}

 int main(){
	 
	 array = squareInit();
	 timerInit();
	 while(1){
		//get information from accelerometer
	}
	return 0;
 }
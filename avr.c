#include <avr/io.h>
#include <util/delay.h>
unsigned char FND_SEGNP[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x6F};//숫자
unsigned char FND_SEGWP[10] = {0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0xA7,0xFF,0xEF};//점있는숫자
unsigned char FND_SEGPOS[4] = {0x01,0x02,0x04,0x08};//세그먼트 자리

//포트 초기화
void init_port(){    
	DDRA = 0xFF;
	DDRF = 0xF0;
	DDRG = 0x00;
	DDRE = 0x0C;
	PORTE = 0x04;
	PORTA = 0x0F;
}

//j값을 각 자리수로 나눠 세그먼트당 출력하는 함수.
void printSeg(int j){
	
    //각각의 세그먼트에 값을 각각 1ms씩 출력을 번갈아가면서함
    //짧은 시간에 반복함으로서 4개를 모두 켜진것처럼 보이게 할수있다.
    //1번째 세그먼트에 값출력
    PORTA = FND_SEGPOS[0];
	PORTE = 0x04;
	PORTE = 0x00;
	PORTA = FND_SEGNP[j/1000];      //1000자리수
	PORTE = 0x08;
	PORTE = 0x00;
	_delay_ms(1);

	//2번째 세그먼트에 값출력
    PORTA = FND_SEGPOS[1];
	PORTE = 0x04;
	PORTE = 0x00;
	PORTA = FND_SEGWP[(j%1000)/100];//100자리수
	PORTE = 0x08;
	PORTE = 0x00;
	_delay_ms(1);

	//3번째 세그먼트에 값출력
    PORTA = FND_SEGPOS[2];
	PORTE = 0x04;
	PORTE = 0x00;
	PORTA = FND_SEGNP[(j%100)/10];  //10자리수
	PORTE = 0x08;
	PORTE = 0x00;
	_delay_ms(1);

	//4번쨰 세그먼트에 값출력
    PORTA = FND_SEGPOS[3];
	PORTE = 0x04;
	PORTE = 0x00;
	PORTA = FND_SEGNP[(j%10)];      //1자리수
	PORTE = 0x08;
	PORTE = 0x00;
	_delay_ms(1);
}

int main(void)
{	
    //포트 초기화
	init_port();
	
    while (1){
		///////////////////////초기값 지정////////////////////////////
        int j = 0;                  //시간값을 초기화 한다.
		int currentButton = 0x0F;   //스위치가 눌린 경우에 눌린 스위치의 값을 저장하는 변수.
                                    //sw5가 두번 눌린 경우엔 스위치의 값을 0x0f로 초기화 할예정
		int stateButton = 0x0F;     //바로 이전 루프의 스위치 상태값을 저장하는 변수.
		printSeg(j);                //초기0000출력
        ///////////////////////초기값 지정 완료////////////////////////////
        

        //////////////////////////타이머 기능 처리부///////////////////////////
		for (; j < 10000; ){//j가 시간값으로 시간값을 9999까지 출력해야 하므로 10000이되면 종료
			
            //이전에 눌렸던 스위치값을 이용해 타이머기능 제어
			switch (currentButton){
			case 0x0E: j++;     break;  //이전에 sw5가 한번(홀수번) 눌린경우 시간값 계속해서 증가
			case 0x0D: j = 0;   break;	//sw6가 눌린경우 시간값을 리셋
			case 0x0B:break;            //다른 스위치가 눌린경우엔 무시한다
			case 0x07:break;            //상동
            default  :break;            //sw5가 두번째(짝수번) 눌린경우엔 시간값을 변경하지않고 그대로 유지한다.
			}

            //세그먼트에 값 출력
			printSeg(j);
			_delay_ms(1);
			printSeg(j);

            //스위치 눌린것 디텍션
            //이전 루프에서 버튼이 눌리지 않았으면서 현재루프에서 버튼이 눌린경우, 
            //즉 fallingedge인 경우를 detact 하여 currentButton에 스위치 값 저장
            //스위치를 땐 뒤에도 스위치값을 변경하지 않고 유지함
			if ((PING&0x0F)!=0x0F && stateButton == 0x0F){
				if(currentButton == 0x0E && (PING&0x0F)==0x0E ){
                    //sw5가 두번째(짝수번째) 눌린경우에 currentButton을 초기화하여 시간값을 정지시킴
                    currentButton = 0x0F;
                }else{
                    //그 외에 경우에는 스위치값을 저장함
					currentButton = PING&0x0F;
				}
			}
            //다음 루프에서 falling edge 감지를 위한 현 루프의 스위치 값 저장
			stateButton = PING&0x0F;
		}
        //////////////////////////////타이머 끝////////////////////////////////////
	}
    return 0;
}


#include "Sea.h"
#include "BoAYoProcess.h"

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int Serv_sock;

void Method_Process(struct sockaddr_in Clin_Addr, char *Network_ID, char *SeaMethod, char *Screen_ID, char *checksum){
    if (strcmp(SeaMethod, "TPCREATE") == 0){
        // 템플릿으로 스크린, 컴포넌트 생성
        
    }
    else if (strcmp(SeaMethod, "SCCREATE") == 0){
        // 스크린 생성
        
    }
    else if (strcmp(SeaMethod, "CMCREATE") == 0){
        // 컴포넌트 생성
    }
    else if (strcmp(SeaMethod, "EVENTCRT") == 0){
        // 이벤트 정보 생성
    }
    else if (strcmp(SeaMethod, "EVENTPRO") == 0){
        // 이벤트 정보 처리
    }
    else if (strcmp(SeaMethod, "SCMOTIFY") == 0){
        // 스크린 수정
    }
    else if (strcmp(SeaMethod, "CMMOTIFY") == 0){
        // 컴포넌트 수정
    }
    else if (strcmp(SeaMethod, "DATAGETS") == 0){
        // 데이터 수신 (이미지, 파일 수신)
    }
    else if (strcmp(SeaMethod, "REVERSES") == 0){
        // 검증, 확인
    }
    else if (strcmp(SeaMethod, "CONNECQS") == 0){
        // 연결 요청
    }
    // 연결 응답인 CONNECRP는 서버에서 전송만 합니다.
    else{
        // 잘못된 메소드
    }
};

void Sea_Protocal_Main(){
    char recvBuffer[2048]; // 수신용 버퍼

    struct sockaddr_in Serv_Addr;
    struct sockaddr_in Clin_Addr;
    unsigned int Clin_Len;
    Serv_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (Serv_sock == -1){
        printf("Socket Error[-1]");
        return;
    }
    memset(&Serv_Addr, 0, sizeof(Serv_Addr));
    Serv_Addr.sin_family = AF_INET;
    Serv_Addr.sin_addr.s_addr = htonl(INADDR_ANY);
    Serv_Addr.sin_port = htons(22117);

    int Bind_Stat = ::bind(Serv_sock, (struct sockaddr*)&Serv_Addr, sizeof(Serv_Addr));
    if (Bind_Stat == -1){
        printf("Recv error");
    }
    while(1){
        Clin_Len = sizeof(Clin_Addr);
        ssize_t Recv_Len = recvfrom(Serv_sock, recvBuffer, 2048, 0, (struct sockaddr*)&Clin_Addr, &Clin_Len);
        if (Recv_Len == -1){
            printf("recv error");
            continue;
        }
        ssize_t i;
        char Network_ID[9], SeaMethod[9], Screen_ID[9], checksum[9];
        std::thread* OneProcess;
        for (i = 0; i <= 8; ++i){
            Network_ID[i] = recvBuffer[i];
        }Network_ID[8] = '\0';
        for (i = 0; i <= 8; ++i){
            SeaMethod[i] = recvBuffer[8 + i];
        }SeaMethod[8] = '\0';
        for (i = 0; i <= 8; ++i){
            Screen_ID[i] = recvBuffer[16 + i];
        }Screen_ID[8] = '\0';
        for (i = 0; i <= 8; ++i){
            checksum[i] = recvBuffer[24 + i];
        }checksum[8] = '\0';

        OneProcess = new std::thread(Method_Process, Network_ID, SeaMethod, Screen_ID, checksum);
        //Method_Process();
    }
}
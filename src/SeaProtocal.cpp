#include "Sea.h"
#include "BoAYoProcess.h"

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <iostream>
#include <list>

int Serv_sock;

std::string splitElements(std::string data, std::string elemName){
    // 요소 나누기
    elemName.append(":");

    size_t start = data.find(elemName);
    if (start == std::string::npos){
        return "";
    }
    size_t end = data.find("\n", start);
    std::string elemIn = data.substr(start + elemName.length() + 1, end - start - elemName.length());
    return elemIn;
}

void Omiss_Add(std::list<std::string>& omissionList, std::string elem){
    omissionList.push_back(elem);
}

float Str_filter_f(std::string txts){
    if (txts == ""){
        return NULL;
    }
    return std::stof(txts);
}

int Str_filter_i(std::string txts){
    if (txts == ""){
        return NULL;
    }
    return std::stoi(txts);
}

std::string get_Hash();

void Method_Process(struct sockaddr_in Clin_Addr, char *Network_ID, char *SeaMethod, char *Screen_ID, char *Hchecksum, char *Dchecksum, std::string Data){
    std::list<std::string> omiss; // 필수 데이터가 오지 않은 경우
    if (strcmp(SeaMethod, "TPCREATE") == 0){
        // 템플릿으로 스크린, 컴포넌트 생성
        
    }
    else if (strcmp(SeaMethod, "SCCREATE") == 0){
        // 스크린 생성
        float sx, sy, sz, sLR, sUD, sH, sW;
        std::string sN = NULL;
        sx = Str_filter_f(splitElements(Data, "ScrnX")); if(sx == NULL){Omiss_Add(omiss, "ScrnX");} // ScrnX
        sy = Str_filter_f(splitElements(Data, "ScrnY")); if(sy == NULL){Omiss_Add(omiss, "ScrnY");} // ScrnY
        sz = Str_filter_f(splitElements(Data, "ScrnZ")); if(sz == NULL){Omiss_Add(omiss, "ScrnZ");} // ScrnZ
        sLR = Str_filter_f(splitElements(Data, "ScrnLR")); if(sLR == NULL){Omiss_Add(omiss, "ScrnLR");} // ScrnLR
        sUD = Str_filter_f(splitElements(Data, "ScrnUD")); if(sUD == NULL){Omiss_Add(omiss, "ScrnUD");} // ScrnUD
        sH = Str_filter_f(splitElements(Data, "ScrnHgt")); if(sH == NULL){Omiss_Add(omiss, "ScrnHgt");} // ScrnHgt
        sW = Str_filter_f(splitElements(Data, "ScrnWth")); if(sW == NULL){Omiss_Add(omiss, "ScrnWth");} // ScrnWth
        sN = splitElements(Data, "ScrnName"); if(sN == ""){Omiss_Add(omiss, "ScrnName");} // ScrnName

        if (omiss.empty()){
            int *ScrID;
            Screen_Info* newScrn = new Screen_Info(sN, sx, sy, sz, sLR, sUD, sH, sW, ScrID);
            Sea_Make_Reverse(Network_ID, 0, "ScreenID:" + std::to_string(*ScrID));
        }
        else{
            Sea_Omission(Network_ID, omiss);
        }
    }
    else if (strcmp(SeaMethod, "CMCREATE") == 0){
        // 컴포넌트 생성
        float cx, cy, cH, cW, cD;
        std::string cN = NULL, cRGBAs = NULL;
        cx = Str_filter_f(splitElements(Data, "CompX")); if(cx == NULL){Omiss_Add(omiss, "CompX");} // CompX
        cy = Str_filter_f(splitElements(Data, "CompY")); if(cy == NULL){Omiss_Add(omiss, "CompY");} // CompY
        cH = Str_filter_f(splitElements(Data, "CompHgt")); if(cH == NULL){Omiss_Add(omiss, "CompHgt");} // CompHgt
        cW = Str_filter_f(splitElements(Data, "CompWth")); if(cW == NULL){Omiss_Add(omiss, "CompWth");} // CompWth
        cD = Str_filter_f(splitElements(Data, "CompDep")); if(cD == NULL){Omiss_Add(omiss, "CompDep");} // CompDep
        cN = splitElements(Data, "CompName"); if(cN == ""){Omiss_Add(omiss, "CompName");} // CompName
        
        cRGBAs = splitElements(Data, "StyleFixed"); // 선택수신요소

        if (omiss.empty()){
            int *CmpnID;
            Component_Info* newComp = new Component_Info(cN, cx, cy, cH, cW, cD, Screen_List[*Screen_ID], CmpnID);
            Sea_Make_Reverse(Network_ID, 0, "ComponentsID:" + std::to_string(*CmpnID));
        }
        else{
            Sea_Omission(Network_ID, omiss);
        }
    }
    else if (strcmp(SeaMethod, "EVENTCRT") == 0){
        // 이벤트 정보 생성
        int Scp_D;
        std::string eT = NULL, TI = NULL, Scp_T = NULL, ;
        eT = splitElements(Data, "EventType"); if(eT == ""){Omiss_Add(omiss, "EventType");} // EventType

        if (omiss.empty()){
            Sea_Make_Reverse(Network_ID, 0, "");
        }
        else{
            Sea_Omission(Network_ID, omiss);
        }
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

void Sea_Make_Reverse(char *NetworkID, bool Error, std::string Data){}

void Sea_Omission(char *NetworkID, std::list<std::string>& omissionList){
    // 내용누락의 경우
}

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
        char Network_ID[9], SeaMethod[9], Screen_ID[9], Hchecksum[9], Dchecksum[9];
        std::thread* OneProcess;
        for (i = 0; i <= 8; ++i){
            Network_ID[i] = recvBuffer[i]; // Sea 프로토콜용 네트워크ID(재검증용)
        }Network_ID[8] = '\0';
        for (i = 0; i <= 8; ++i){
            SeaMethod[i] = recvBuffer[8 + i]; // Sea 프로토콜용 헤더
        }SeaMethod[8] = '\0';
        for (i = 0; i <= 8; ++i){
            Screen_ID[i] = recvBuffer[16 + i]; // Sea 프로토콜용 스크린ID
        }Screen_ID[8] = '\0';
        for (i = 0; i <= 8; ++i){
            Hchecksum[i] = recvBuffer[24 + i]; // 헤더용 체크섬
        }Hchecksum[8] = '\0';
        for (i = 0; i <= 8; ++i){
            Dchecksum[i] = recvBuffer[31 + i]; // 데이터용 체크섬
        }Dchecksum[8] = '\0';
        std::string datas(recvBuffer); // 헤더 부분을 제외한 데이터들
        datas.erase(0,39); // 헤더 부분 삭제

        OneProcess = new std::thread(Method_Process, Network_ID, SeaMethod, Screen_ID, Hchecksum, Dchecksum, datas);
        //Method_Process();
    }
}
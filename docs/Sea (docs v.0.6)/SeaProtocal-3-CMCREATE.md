# CMCREATE
메소드 CMCREATE는 헤더에 포함된 스크린 위에서 컴포넌트을 직접 생성할 때 사용하는 메소드 입니다.<br>

## 필수 수신 요소
**CompX** - 컴포넌트 위치의 X좌표를 실수(float)타입으로 수신하고 해당 X좌표를 생성되는 컴포넌트에 지정합니다.<br>
**CompY** - 컴포넌트 위치의 Y좌표를 실수(float)타입으로 수신하고 해당 Y좌표를 생성되는 컴포넌트에 지정합니다.<br>
**CompHgt** - 컴포넌트의 높이를 실수(float)타입으로 수신하고 해당 높이를 생성되는 컴포넌트에 지정합니다.<br>
**CompWth** - 컴포넌트의 너비를 실수(float)타입으로 수신하고 해당 너비를 생성되는 컴포넌트에 지정합니다.<br>
**CompDep** - 컴포넌트의 깊이를 실수(float)타입으로 수신하고 해당 너비를 생성되는 컴포넌트에 지정합니다.<br>
**CompName** - 컴포넌트 이름을 string타입으로 수신하고 해당 이름을 컴포넌트의 이름으로 지정합니다. 

## 선택 수신 요소
**StyleFixed** - 고정된 컴포넌트의 모습을 출력하기 위해 사용합니다. RGBA값을 2바이트로 합친 배열을 string타입으로 전송합니다. Alpha는 0을 제외하고  이것을 사용하면 StyleEdge*, StyleSide* 요소가 무시됩니다.<br>
**StyleEdgeTop** - 모서리 윗부분의 모습을 지정할때 사용합니다. RGBA값을 합친 string타입으로 전송합니다.<br>
**StyleEdgeBottom** - 모서리 아래부분의 모습을 지정할때 사용합니다. RGBA값을 합친 string타입으로 전송합니다.<br>
**StyleEdgeLeft** - 모서리 왼쪽부분의 모습을 지정할때 사용합니다. RGBA값을 합친 string타입으로 전송합니다.<br>
**StyleEdgeRight** - 모서리 오른쪽부분의 모습을 지정할때 사용합니다. RGBA값을 합친 string타입으로 전송합니다.<br>
**StyleEdgeLT** - 꼭짓점 좌상단 부분의 모습을 지정할때 사용합니다. RGBA값을 합친 string타입으로 전송합니다.<br>
**StyleEdgeRT** - 꼭짓점 우상단 부분의 모습을 지정할때 사용합니다. RGBA값을 합친 string타입으로 전송합니다.<br>
**StyleEdgeLB** - 꼭짓점 좌하단 부분의 모습을 지정할때 사용합니다. RGBA값을 합친 string타입으로 전송합니다.<br>
**StyleEdgeRB** - 꼭짓점 우하단 부분의 모습을 지정할때 사용합니다. RGBA값을 합친 string타입으로 전송합니다.

## REVERSES 여부 및 REVERSE 동작시 전송되는 요소
**REVERSES가 동작합니다.**
수신된 모든 요소를 다시 전송, 검증합니다. 체크섬도 함께 전송합니다.
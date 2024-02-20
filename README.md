# [Project]
- subject name : miniRT
- team name: 독박RT🍼
- member: `@dongyeuk` (dongyeuk@student.42seoul.kr) `@jaejilee` (jaejilee@student.42seoul.kr)

# [Build and Execute]
## Build
```bash
git clone git@github.com:JJaeJin/miniRT.git
cd miniRT
make
```
Then, you can see `miniRT` file.
## Execute
To execute miniRT, you need formatted file with `.rt` expansion.
```bash
./miniRT example.rt
```
## Test Environment
- OS: macOS Catalina 10.15.7
- g++: Apple clang version 12.0.0
- library: minilibX

# [Development Process]
## 목표
- 기한: 2024.02.16 ~ 2024.03.15
- 점수: 125점 달성
## 학습 목표
- 그래픽 렌더링 공부
- ray casting, ray tracing 기법 공부
- 깃 & 깃허브 협업 심화 공부 (+ pull request)
## 진행 상황
**2024.02.16** 과제 등록, git repository 만들기, README 작성  
**2024.02.17** 규칙 정하기 (커밋 메세지, 풀 리퀘스트)  
**2024.02.20** parsing 구현 완료  

# [Rules]
## commit message

변경 : "[mod] details"  
추가 : "[add] details"  
삭제 : "[del] details"  
긴급 : "[fix] details"  
## allowed functions
```c
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "mlx.h"
```

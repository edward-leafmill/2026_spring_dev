# C/C++ 실습 환경 (VS Code + MSYS2 UCRT64 + CMake)

## 프로젝트 구조

```
C:\hello
├─ .gemini/
│  └─ settings.json         ← Gemini Agent Mode 설정
├─ .vscode/                 ← VS Code 설정 (수정하지 마세요)
│  ├─ settings.json
│  ├─ tasks.json
│  ├─ launch.json
│  └─ c_cpp_properties.json
├─ CMakeLists.txt           ← 루트 CMake 설정
└─ labs/                    ← 실습 과제 폴더
   ├─ CMakeLists.txt        ← q* 폴더 자동 탐색
   ├─ q01/
   │  ├─ CMakeLists.txt
   │  └─ main.cpp
   └─ q02/
      ├─ CMakeLists.txt
      └─ main.cpp
```

## 1. 사전 준비

### 1-1. MSYS2 설치
- 설치 경로: **반드시 `C:\msys64`** (기본값 유지)
- 다운로드: https://www.msys2.org

### 1-2. UCRT64 도구 설치
MSYS2 터미널(UCRT64)을 열고 아래 명령 실행:

```bash
pacman -Syu
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-gdb mingw-w64-ucrt-x86_64-cmake
```

설치 확인:

```bash
g++ --version       # GCC 확인
gdb --version       # 디버거 확인
cmake --version     # CMake 확인
```

### 1-3. VS Code 확장 설치
- **C/C++** (Microsoft)
- **CMake Tools** (Microsoft)

## 2. 빌드 & 실행

### 먼저 타깃(문제 번호) 바꾸기
1. VS Code 하단 상태 표시줄에서 **CMake Launch Target** 클릭
2. 실행할 타깃 선택 (예: `lab_q01`, `lab_q04`)
3. 이후 `F5`/`Ctrl+F5`는 선택된 타깃 기준으로 동작

### 단축키별 실제 동작 (이 프로젝트 기준)

| 단축키 | 실행 명령 성격 | 실제 체인 |
|------|------|------|
| `Ctrl+Shift+B` | 전체 빌드 | `configure (cmake UCRT64)` → `CMake: build all` (`course_all_labs`) |
| `F5` | 디버그 실행 | `configure` → `CMake: build launch target` → GDB 연결 실행 |
| `Ctrl+F5` | 디버그 없이 실행 | `configure` → `CMake: build launch target` → 일반 실행 |
| `Ctrl+Shift+F5` | CMake 컨텍스트에서 CMake 실행 | `cmake.launchTarget` (CMake: Run Without Debugging) 실행 |

핵심 포인트:
- 현재 `launch.json`의 `preLaunchTask`가 `CMake: build launch target`이라서, `F5`와 `Ctrl+F5` 모두 실행 전에 현재 Launch Target을 먼저 빌드합니다.
- `tasks.json`의 `CMake: build launch target`은 `${command:cmake.launchTargetName}`만 빌드하므로 전체 빌드보다 보통 빠릅니다.
- `Ctrl+Shift+F5`는 CMake Tools 확장의 기본 키바인딩입니다.
- 현재 프로젝트는 `cmake.buildBeforeRun = true`라서 `Ctrl+Shift+F5`(`cmake.launchTarget`) 실행 시에도 Launch Target을 먼저 빌드합니다(변경 없으면 증분 빌드로 빠르게 통과).
- `Ctrl+Shift+F5`는 컨텍스트 기반으로 동작합니다: 디버그 세션 중(`inDebugMode`)에는 VS Code 기본 `Debug: Restart`가 동작하고, 디버그 세션이 아닐 때 CMake 키바인딩이 동작합니다.

### 실제 속도 비교 (이 저장소에서 측정)

동일 조건( `labs/q04/main.cpp` 변경 후 )에서 빌드 시간:
- `cmake --build build --target lab_q04`: 약 **1.503초**
- `cmake --build build --target course_all_labs`: 약 **2.246초**
- `build/labs/q04/lab_q04.exe` 실행 자체: 약 **0.093초**

정리:
- 타깃 1개만 수정하며 반복 실행할 때는 Launch Target 단위 빌드가 더 빠릅니다.
- `Ctrl+Shift+B`(전체 빌드)는 여러 타깃의 의존성/상태를 한 번에 점검할 때 적합합니다.
- `Ctrl+F5`는 이 프로젝트에서 "추가 작업"을 크게 더 하는 것이 아니라, `launch.json` 기준으로 **configure + launch target 빌드 + 실행** 체인을 수행합니다.

### F5 / Ctrl+F5 / Ctrl+Shift+F5 확인 방법

1. `Ctrl+Shift+P` → `Developer: Toggle Keyboard Shortcuts Troubleshooting`
2. 각 단축키를 눌러 최종 `commandId` 확인
3. 보통 `F5=workbench.action.debug.start`, `Ctrl+F5=workbench.action.debug.run`이고, `Ctrl+Shift+F5`는 컨텍스트에 따라 `cmake.launchTarget` 또는 `workbench.action.debug.restart`가 잡힙니다.

### 터미널에서 직접 빌드 (참고)

```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build --target course_all_labs
```

특정 타깃만 빌드:

```bash
cmake --build build --target lab_q01
```

### C++23 `std::print` / `std::println` 지원

루트 [`CMakeLists.txt`](./CMakeLists.txt)에는 학기 공통 C++23 설정용
`course_cpp23_support`가 정의되어 있습니다.

- C++ Lab 타깃(`q*`)은 이 공통 설정을 통해 C++23 기능을 사용합니다.
- MSYS2 UCRT64의 MinGW GCC에서는 `std::print` / `std::println` 사용 시
  추가 런타임 라이브러리 `stdc++exp`가 필요하므로, 이 설정을 프로젝트 공통으로 연결합니다.
- 참고: GCC 공식 문서도 Windows에서 `std::print` 사용 시 `-lstdc++exp`가 필요하다고 안내합니다.

즉, 학생들은 각 과제별 `CMakeLists.txt`에서 `std::print` 때문에 별도 링크 옵션을 추가할 필요가 없습니다.

## 3. 과제 추가 방법

새 과제 `q03`을 추가하려면:

**1단계.** `labs/q03/` 폴더를 만들고 `main.cpp`를 작성합니다.

**2단계.** `labs/q01/CMakeLists.txt`를 `labs/q03/`에 복사합니다.
이 파일에는 학기 공통 C++23 설정(`enable_course_cpp23`)이 이미 포함되어 있습니다.

```
labs/q03/
├─ CMakeLists.txt    ← q01에서 복사 (수정 불필요)
└─ main.cpp          ← 과제 코드 작성
```

끝입니다. `labs/CMakeLists.txt`가 `q*` 폴더를 자동 탐색하므로 다른 파일은 수정할 필요가 없습니다.

빌드 타깃 이름은 자동으로 `lab_q03`이 됩니다.

## 4. 제출 전 체크리스트

1. VS Code 기본 터미널이 **MSYS2 UCRT64**인지 확인
2. GDB 경로가 **UCRT64**인지 확인 (`C:\msys64\ucrt64\bin\gdb.exe`)
3. 하단 상태 표시줄의 Launch Target이 실제 타깃(`lab_q01`, `lab_q02` 등)인지 확인
4. `Ctrl+Shift+B` → 빌드 성공
5. `Ctrl+F5` → 실행 성공
6. `F5` → 디버그 시작 성공
7. `build/compile_commands.json` 파일 생성 확인
8. 실행 시 `0xc0000135` 또는 `api-ms-win-crt-*` 에러가 나면 → **5. 문제 해결** 참고

## 5. 문제 해결

| 증상 | 해결 |
|------|------|
| `g++`/`cmake` 명령을 못 찾음 | MSYS2 UCRT64 터미널에서 1-2 설치 명령 재실행 |
| VS Code에서 빌드 실패 | VS Code를 완전히 종료 후 재실행 |
| IntelliSense 헤더 오류 (빨간 밑줄) | `Ctrl+Shift+P` → "C/C++: Edit Configurations" → compilerPath가 `C:\msys64\ucrt64\bin\g++.exe`인지 확인 |
| `Ctrl+F5` / `F5` 시 프로그램을 못 찾음 | 하단 상태 표시줄에서 올바른 **CMake Launch Target**을 선택했는지 확인 |
| `F5`와 `Ctrl+F5`가 반대로 보임 | 실행 구성 이름이나 아이콘이 아니라 실제 명령(`debug.start` / `debug.run`)을 Keyboard Shortcuts Troubleshooting으로 확인 |
| `where g++` 결과가 여러 개 | `mingw64`와 `ucrt64` 혼용 금지 — `ucrt64\bin` 하나만 PATH에 유지 |
| 실행 시 `api-ms-win-crt-*.dll` 못 찾음 | 아래 **DLL 로딩 오류** 항목 참고 |
| `std::print` 사용 시 `undefined reference` 링크 에러 | 해당 Lab의 `CMakeLists.txt`가 `enable_course_cpp23(...)`를 포함하는지 확인 |

### DLL 로딩 오류 (`api-ms-win-crt-*.dll` / `0xc0000135`)

실행 시 다음과 같은 에러가 발생할 수 있습니다:

```
error while loading shared libraries: api-ms-win-crt-string-l1-1-0.dll:
cannot open shared object file: No such file or directory
```

**원인:** MSYS Bash 터미널과 Windows 디버거/실행기의 **실행 계층 충돌**입니다.

- `cppdbg`(WindowsDebugLauncher.exe)는 Windows 프로세스 체인으로 실행되어야 하는데, MSYS Bash 경로를 경유하면서 PATH가 꼬임
- Windows는 PATH 구분자로 `;`을 쓰고, MSYS/Linux는 `:`을 씀 — Bash 환경에 Windows식 PATH를 직접 주입하면 경로가 깨져서 런타임 DLL을 못 찾게 됨

**해결 방법 (이 프로젝트의 설정):**

1. **터미널 역할 분리**
   - 사용자 기본 터미널: **MSYS2 UCRT64** 유지 (개발 편의)
   - 자동 실행(빌드/디버그): **cmd.exe**로 고정 (`automationProfile.windows`)

2. **런치 구성 단순화**
   - `launch.json`은 `cmake.launchTargetPath` / `cmake.launchTargetDirectory`를 직접 사용
   - 불필요한 추가 디버그 설정(`cmake.debugConfig`, 강제 `internalConsole`)을 제거하여 `hello_simple`과 같은 흐름으로 유지

3. **PATH 정리**
   - 디버그 환경 PATH: `C:\Windows\System32;C:\msys64\ucrt64\bin;...` (Windows 시스템 경로 우선)
   - 터미널 전역 PATH 오버라이드(`terminal.integrated.env.windows`) 제거
   - MSYS2 터미널에 `MSYS2_PATH_TYPE=inherit` 설정으로 Windows PATH 자연 상속

**확인 방법:**

```bash
echo $MSYSTEM          # UCRT64여야 정상
echo $MSYS2_PATH_TYPE  # inherit여야 정상
```

**한 줄 요약:** 컴파일은 성공했지만 실행 계층과 PATH가 섞여 디버거 시작 시 DLL 로딩이 실패한 문제이며, **터미널/디버그 환경 분리 + PATH 정리**로 해결합니다.

## 6. Gemini Code Assist Agent Mode (Windows)

VS Code에서 Gemini Code Assist의 Agent Mode를 사용하려면 아래 설정이 필요합니다.

### 6-1. Preview Features 활성화

Agent Mode는 Preview 기능이므로 **프로젝트 레벨**에서 활성화해야 합니다.
이 프로젝트에는 이미 `.gemini/settings.json`이 포함되어 있습니다.

```json
{ "general": { "previewFeatures": true } }
```

> **주의:** 시스템 레벨(`C:\Users\<username>\.gemini\settings.json`)에 설정해도
> VS Code Agent Mode에는 적용되지 않습니다. 반드시 프로젝트 루트의
> `.gemini/settings.json`에 설정해야 합니다.
> ([Google 공식 문서](https://developers.google.com/gemini-code-assist/docs/gemini-3))

### 6-2. Windows 경로 문제: Non-ASCII 사용자 이름

Windows 사용자 이름에 **한글 등 non-ASCII 문자**가 포함되어 있으면
VS Code 확장 경로(`C:\Users\한글이름\.vscode\extensions\...`)에서
UTF-8 인코딩 오류가 발생하여 Agent Mode가 동작하지 않을 수 있습니다.

**해결 방법:** extensions 디렉토리를 ASCII 경로로 이동합니다.

```powershell
# 방법 1: 환경변수 (권장, 영구 적용)
setx VSCODE_EXTENSIONS "C:\VSCode\extensions"

# 방법 2: 심볼릭 링크
mklink /D "%USERPROFILE%\.vscode\extensions" "C:\VSCode\extensions"

# 방법 3: 실행 시 플래그 (매번 지정 필요)
code --extensions-dir="C:\VSCode\extensions"
```

관련 이슈:
- [vscode #206512](https://github.com/microsoft/vscode/issues/206512) — extensions 경로의 non-ASCII 문자로 확장 실패
- [cloud-code-vscode #1181](https://github.com/GoogleCloudPlatform/cloud-code-vscode/issues/1181) — non-UTF-8 로캘에서 Agent 중단

### 6-3. VS Code User Setup vs System Setup (bin 폴더 문제)

VS Code에는 두 가지 설치 방식이 있으며, 경로가 다릅니다.

| 설치 방식 | 경로 |
|-----------|------|
| **User Setup** | `C:\Users\<username>\AppData\Local\Programs\Microsoft VS Code` |
| **System Setup** | `C:\Program Files\Microsoft VS Code` |

User Setup에서 System Setup으로 (또는 그 반대로) **전환 설치**하면
Gemini Code Assist 확장이 이전 설치의 `bin/` 폴더 경로를 참조하여
Agent Mode 활성화에 실패할 수 있습니다.

**증상:** Agent Mode에서 명령 실행 불가, "Failed to connect" 오류

**해결 방법:** VS Code 설치 루트의 `bin/` 폴더를 확장이 참조하는
commit-hash 디렉토리 안에 수동 복사합니다.

```
VS Code 설치 루트/
├─ bin/                    ← 이 폴더를
│  ├─ code.cmd
│  └─ ...
└─ <commit-hash>/          ← 이 안에 복사
   ├─ bin/                 ← (복사된 bin)
   └─ resources/
```

```powershell
# 예시 (commit-hash는 설치마다 다름, 실제 폴더명 확인 필요)
$vscode = "$env:LOCALAPPDATA\Programs\Microsoft VS Code"
$hash = Get-ChildItem $vscode -Directory | Where-Object { $_.Name -match '^[0-9a-f]{10}' }
Copy-Item "$vscode\bin" "$vscode\$($hash.Name)\bin" -Recurse -Force
```

> **참고:** 이 작업은 VS Code **업데이트마다 반복**해야 합니다.
> 가능하면 한 가지 설치 방식만 사용하고 전환하지 않는 것이 좋습니다.
>
> 이 문제는 **Cursor IDE** 등 VS Code 포크에서도 동일하게 발생합니다.
> ([참고](https://dredyson.com/fix-gemini-code-assist-agent-mode-in-cursor-my-complete-step-by-step-workaround-after-6-months-of-struggle/))

## 7. 환경 설정 요약 (`.vscode/` 내용 설명)

이 프로젝트의 `.vscode/` 설정은 **시스템 PATH에 의존하지 않고** 도구 경로를 직접 지정합니다. 따라서 학생 PC마다 PATH가 달라도 동일하게 동작합니다.

핵심 설계: **MSYS 터미널과 Windows 디버거는 실행 계층이 다르므로 역할을 분리**합니다.

- **settings.json**:
  - 기본 터미널: MSYS2 UCRT64 (`msys2_shell.cmd -ucrt64`), `MSYS2_PATH_TYPE=inherit`로 Windows PATH 상속
  - 자동화 프로필(`automationProfile.windows`): **cmd.exe**로 고정 — 빌드/디버그 Task가 Bash를 경유하지 않도록 분리
  - CMake 경로/Generator와 `cmake.buildDirectory`를 명시
  - `cmake.buildBeforeRun = true`로 설정하여, CMake 실행 명령(`Ctrl+Shift+F5`)에서도 실행 전 빌드를 보장
- **tasks.json**:
  - `cmake.exe`를 직접 호출하는 shell Task로 configure/build 수행
  - `Ctrl+Shift+B` 기본 빌드는 전체 프로젝트를 빌드
  - 실행/디버그 전에는 `CMake: build launch target` Task로 현재 선택한 Launch Target만 빌드
- **launch.json**:
  - 실행 구성 이름을 **Debug CMake launch target**으로 명확히 유지하여 의미 혼동을 줄임
  - GDB 디버거 경로 고정 (`C:\msys64\ucrt64\bin\gdb.exe`)
  - 디버그 PATH: `C:\Windows\System32;C:\msys64\ucrt64\bin;...` (Windows 시스템 경로 우선)
  - 실행 파일/작업 디렉터리를 `cmake.launchTargetPath`, `cmake.launchTargetDirectory`로 자동 연결
  - `preLaunchTask`로 현재 Launch Target을 먼저 빌드한 뒤 `F5` / `Ctrl+F5` 실행
- **키보드 단축키**:
  - 이 프로젝트의 `.vscode`에는 F5/Ctrl+F5 키를 바꾸는 설정이 없음
  - 키 동작은 VS Code 기본 키바인딩과 사용자 전역 설정이 결정
- **c_cpp_properties.json**: IntelliSense가 UCRT64 컴파일러와 `compile_commands.json`을 사용하도록 지정

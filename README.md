# ThaiThuong-PCCU_OOP_1B
# 🌿 野生動物生存模擬

一個以 C++ 實作的離散時間 2D 生態系模擬，透過狼、兔子與植物在方格地圖上的互動，展示核心物件導向程式設計概念——繼承、多型、抽象、封裝與動態分派。

---

## 組別資訊 

- 組別號碼：第 9 組
- 系級班級：資工 1B
- 成員:范裴太愴 (組長), 馮家輝  

---

## 小專題題目

野生動物生存模擬系統設計與實作

模擬狼、兔子與植物在生態環境中的互動，
展示物件導向程式設計中的繼承、多型、
封裝與抽象等核心概念。

---

## 📋 目錄

- [概述](#概述)
- [UML圖](#UML圖)
- [專案結構](#專案結構)
- [運作方式](#運作方式)
- [快速開始](#快速開始)
- [遊玩方式](#遊玩方式)
- [展示的物件導向概念](#展示的物件導向概念)
- [已知問題](#已知問題)
- [分工資訊](#分工資訊)

---

## 概述

每個回合，方格上的每個實體都依照其物種規則行動。狼獵食兔子，兔子啃食植物，植物則向外蔓延。能量驅動生存——能量耗盡的動物會死亡，能量充足的動物則會繁殖。模擬持續進行，直到使用者選擇退出。

世界以 `20 × 10` 的字元方格形式渲染於終端機中。

---

## 專案結構

```
SurvivalWorldSimulation/
│
├── SurvivalWorldSimulation.cpp   # main() — 程式進入點，選單迴圈
│
├── World.h / World.cpp           # 方格、實體容器、更新迴圈
│
├── Entity.h / Entity.cpp         # 基礎類別 — 位置 (x, y)
│
├── Animal.h / Animal.cpp         # 抽象類別 — 能量、物種、虛擬行為
│
├── Wolf.h / Wolf.cpp             # 捕食者 — 獵食兔子，初始能量 40，能量 ≥ 60 時繁殖
│
├── Rabbit.h / Rabbit.cpp         # 草食動物 — 啃食植物，初始能量 50，能量 ≥ 80 時繁殖
│
└── Plant.h / Plant.cpp           # 食物來源 — 被動生長與蔓延
```
`World` 是模擬控制器。它透過 `vector<Animal*>` 與 `vector<Plant*>`（原始指標，手動管理）擁有所有實體，並仲介所有互動——實體之間不會直接溝通。

---

## UML圖
<img width="1689" height="1043" alt="UML" src="https://github.com/user-attachments/assets/a77aa119-9fce-4b42-beea-4bed813be07e" />


---

## 運作方式

### 回合順序（`World::update()` 內部）

<img width="400" height="440" alt="Ảnh chụp màn hình 2026-06-04 175720" src="https://github.com/user-attachments/assets/08810ae7-2f21-4199-b70c-7baf9fddf78f" />

每次呼叫 `update()` 皆依照以下固定順序執行：

1. **狼的階段** — 每隻存活的狼依序呼叫 `move()` → `eat()` → `reproduce()`
2. **動物清理** — 死亡的動物（能量 ≤ 0 或被吃掉）被移除並釋放記憶體
3. **兔子的階段** — 每隻存活的兔子依序呼叫 `move()` → `eat()` → `reproduce()`
4. **動物清理** — 死亡的動物（能量 ≤ 0 或被吃掉）被移除並釋放記憶體
5. **清空生成佇列** — 第 1–4 步中排入佇列的所有新生動物加入存活向量
6. **植物的階段** — 每株植物呼叫 `grow()` → `spread()`
7. **清空植物佇列** — 新蔓延的植物加入存活向量

### 實體行為

| 實體 | 移動 | 進食 | 繁殖 |
|------|------|------|------|
| 狼 | 尋找鄰近兔子；否則隨機移動 | 殺死同格的兔子（+15 能量） | 需要能量 ≥ 60；消耗 40 能量 |
| 兔子 | 尋找鄰近植物；否則隨機移動 | 移除同格的植物（+20 能量） | 需要能量 ≥ 80；消耗 40 能量 |
| 植物 | — | — | 當 `growCounter ≥ 30` 時向相鄰格蔓延 |


---

## 快速開始

### 環境需求

- C++11 或更新版本
- 任何標準 C++ 編譯器（g++、clang++、MSVC）

### 編譯

```bash
# g++
g++ -std=c++11 -o simulation \
    SurvivalWorldSimulation.cpp \
    World.cpp Animal.cpp Wolf.cpp Rabbit.cpp Plant.cpp Entity.cpp

# clang++
clang++ -std=c++11 -o simulation \
    SurvivalWorldSimulation.cpp \
    World.cpp Animal.cpp Wolf.cpp Rabbit.cpp Plant.cpp Entity.cpp
```

### 執行

```bash
./simulation
```

---

## 遊玩方式

```
Set the number of wolfs:          3
Set the number of rabbits:        10
Set the number of grass:          20

--------------------------
Turn: 0
.  .  .  .  .  G  .  .  .  .
.  .  .  .  .  G  .  G  .  .
.  .  .  G  .  G  .  .  .  W
.  .  .  .  .  .  .  .  .  .
.  .  .  .  .  .  .  .  .  .
.  .  G  .  .  .  .  .  .  .
.  .  .  .  .  G  R  .  .  .
.  .  G  .  .  .  R  .  .  .
.  .  .  .  .  .  R  .  .  G
G  .  .  .  G  W  .  .  .  .
G  .  .  .  .  .  .  .  G  .
.  .  .  .  .  .  .  .  .  .
.  .  .  .  .  .  G  .  .  .
.  .  .  .  .  .  .  .  .  .
.  .  .  R  G  .  R  .  R  .
.  .  G  .  .  .  .  R  .  .
.  .  .  .  .  R  .  .  .  .
.  .  G  .  R  .  .  .  .  .
.  R  G  .  .  W  .  .  G  .
G  .  .  .  .  .  .  .  .  .

Current wolf population:3
Current rabbit population:10
Current grass population:20

--------------------------

1.  Next turn
2.  Next 10 turns
3.  Exit
```

### 圖例說明

| 符號 | 實體 |
|------|------|
| `W` | 狼 |
| `R` | 兔子 |
| `G` | 草／植物 |
| `.` | 空格 |

### 狼與兔子的互動過程

下圖展示狼（W）與兔子（R）在地圖中的互動情況。  
狼會在周邊地區捕獵。

| 互動前 | 互動後 |
|--------|--------|
| <img width="286" height="345" alt="Screenshot 2026-06-03 010943" src="https://github.com/user-attachments/assets/2b6fc089-23c9-4a83-bd83-12a04026cb05" />| <img width="286" height="345" alt="Screenshot 2026-06-03 010956" src="https://github.com/user-attachments/assets/39087ec3-43fe-4666-82c0-5de23f0149c8" />|

### 程式碼
<img width="664" height="682" alt="Ảnh chụp màn hình 2026-06-06 013743" src="https://github.com/user-attachments/assets/9333b217-6245-4355-a223-22093fb6fbc6" />

## 🌱 植物生長與擴散展示

下圖展示植物（G）在模擬過程中的生長與擴散行為。

在第 2 回合時，地圖上的植物數量為 **9 株**；經過一回合更新後，部分植物成功向周圍空格擴散，使第 3 回合的植物數量增加至 **18 株**。

此結果顯示植物會隨時間持續成長，並逐漸佔據更多可用空間，為兔子提供穩定的食物來源，進而影響整個生態系統的族群變化。

| 互動前 | 互動後 |
|-------------------|-------------------|
|<img width="286" height="530" alt="Screenshot 2026-06-03 011011" src="https://github.com/user-attachments/assets/8c02a9f8-c709-456a-81c0-5241170853f6" />| <img width="286" height="530" alt="Screenshot 2026-06-03 011016" src="https://github.com/user-attachments/assets/1272de2a-23dd-4bd3-905f-a0dcc080db79" />|

### 程式碼

<img width="467" height="452" alt="Ảnh chụp màn hình 2026-06-06 013952" src="https://github.com/user-attachments/assets/e280f2c3-6763-4df9-8c64-4d405288b240" />

此互動展示了系統中的捕食邏輯：狼會尋找附近的兔子，並在移動後進行獵食；兔子若被狼捕食，會從地圖中移除，同時狼會獲得能量。

## 🐰 兔子進食與繁殖展示

下圖展示兔子（R）透過進食植物獲得能量後進行繁殖的過程。

經過一回合更新後，第 5 回合的兔子數量增加至 **7 隻**，而植物數量下降至 **14 株**。這代表兔子透過啃食植物獲得能量，並在能量達到門檻後產生新的兔子。

| 互動前 | 互動後 |
|-------------------|-------------------|
| <img width="286" height="555" alt="Screenshot 2026-06-03 011037" src="https://github.com/user-attachments/assets/148f56f6-ff15-4380-81a0-a7908612e184" />|<img width="286" height="555" alt="Screenshot 2026-06-03 011042" src="https://github.com/user-attachments/assets/7a81653c-09b9-446a-903a-edce27b50426" />|

### 程式碼

<img width="560" height="500" alt="Ảnh chụp màn hình 2026-06-06 013930" src="https://github.com/user-attachments/assets/7d8b8580-c7ce-4865-84a7-9a49a6f193d5" />

## 展示的物件導向概念

| 概念 | 位置 |
|------|------|
| **繼承** | `Wolf`、`Rabbit` → `Animal` → `Entity`；`Plant` → `Entity` |
| **多型** | `move()`、`eat()`、`reproduce()` 在 `Animal` 中為純虛擬函式；透過 `Animal*` 指標在執行期解析 |
| **抽象** | `Animal` 無法被實例化——它定義介面，子類別提供實作 |
| **封裝** | `Entity` 將 `x, y` 設為私有；`World` 將其向量設為私有；外部程式碼透過存取方法操作 |
| **組合** | `World` 擁有所有實體（堆積配置，移除時手動刪除） |
| **動態配置** | 模擬過程中大量使用 `new Wolf(...)`、`new Rabbit(...)`、`new Plant(...)` |
| **延遲刪除** | 死亡旗標＋清理階段，避免更新迴圈中的迭代器失效 |
| **前向宣告** | `Animal.h` / `Plant.h` 中的 `class World;` 解決循環 `#include` 依賴 |

---

## 已知問題

- **狼優先的回合偏差** — 每個回合狼始終在兔子之前行動，使捕食者獲得系統性優勢。若每輪隨機化行動順序，將產生更均衡的族群動態。
- **`growCounter` 從不重置** — 植物蔓延後，其計數器持續累加。此後每回合都會嘗試蔓延，僅受鄰近格的可用性限制。

---

## 分工資訊

| 姓名 | 開發內容 |
|------|----------|
| 范裴太愴 |  主要程式碼編輯,PPT| 
| 馮家輝 | README |

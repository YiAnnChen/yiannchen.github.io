# FTEC v4 組合式證明：嚴格重述、推導與程式對照

撰寫日期：2026-11-22。對應程式：`ftec_compositional_v4/`（原版）與 `ftec_compositional_v4_1/`（修正版）。本文件就是 v4 README 第一行連結的「證明審查補充」。

## 1. 定理與適用範圍

**模型。** Steane $[[7,1,3]]$ 碼，資料位元 q0…q6，症狀輔助位元 q7，旗標位元 q8。每輪依序量測 3 個 Z 型穩定子和 3 個 X 型穩定子，每個量測電路有 10 個操作：op0、op1 是症狀、旗標的準備；op2…op7 是 6 個 CNOT；op8、op9 是症狀、旗標的量測。終止規則：若某輪任一旗標為 1，再做兩輪完整量測後停止並走旗標分支；否則連續三輪症狀相同就停止，走一般分支。

**故障模型（t=1）。** 合法配置只有三種：無錯誤；一個重量一的初始資料錯誤（r=1, s=0，共 21 種）；或乾淨基線前三輪內的一個電路故障（r=0, s=1）。電路故障包含準備翻轉、CNOT 之後任意非恆等的兩位元 Pauli（15 種）、量測翻轉，共 3×6×94=1692 種。合計 1714 種有效配置。模型不含 idle、古典控制或修正操作的故障。因為只有一次故障，而且故障前的控制流程必然與乾淨的三輪相同，「只在第 1～3 輪」這個限制在此模型內是完整的。

**Decoder。** 一般分支用最後一輪症狀做 Hamming 解碼；旗標分支查一張由原 Python 參考模型窮舉產生、共 288 項的完整歷史表。

**定理（本模型內）。** 對任意兩個合法執行 $f_1,f_2$，若它們的完整觀測相同，也就是輪數 $n$、分支 $b$ 與每輪 12 位元記錄 $h_0,\dots,h_7$ 都相同，則

$$\sigma(E_1^\dagger E_2)=0 \;\Longrightarrow\; E_1^\dagger E_2\in S\quad(\text{忽略全域相位}),$$

其中 $E_i$ 是第 $i$ 次執行結束時、**修正前**的資料 Pauli 錯誤，$\sigma$ 是理想症狀，$S$ 是穩定子群。若保留實際算子的相位，結論應寫成 $E_1^\dagger E_2\in\Phi S$。

這個定理**不**涵蓋：t>1；r+s>1；任意（不受預算限制的）初始錯誤，也就是定義 3.4 中要求任意輸入的那一項；其他碼或其他 decoder。原本直接展開兩次協定的 pair 模型，仍然停留在 UNKNOWN／ERROR，沒有被這份證明改判為 TRUE。

## 2. 記號與程式對應

Pauli 以兩個 7 位元遮罩 $(x,z)$ 表示，第 $q$ 位為 1 代表 q 位上有 X（或 Z）成分，Y 就是兩個都為 1。乘法對應位元 XOR，忽略相位。

- `parity(v)`：$v$ 的位元奇偶。
- `sy(x,z)`：6 位元症狀。低 3 位是 $x$ 與 $H=\{120,102,85\}$ 各列的奇偶（由 Z 型穩定子量到），高 3 位是 $z$ 的對應奇偶。
- `member(x,z)`：`sy==0 && parity(x)==0 && parity(z)==0`。Steane 穩定子的 X、Z 部分各自屬於 $H$ 的列空間，這個空間恰好是「三位 Hamming 症狀為零且總奇偶為偶」的 3 維子空間，所以 member 精確等於 $(x,z)\in S$。我已在 Python 窮舉 $2^{14}$ 種 $(x,z)$，結果與暴力列舉 64 個穩定子相同。
- `residual(x,z,s)`：$\mathrm{wt}_{\min}(x,z)\le s$，其中 $\mathrm{wt}_{\min}(P)=\min_{T\in S}\mathrm{wt}(PT)$。實作是檢查 $P$ 本身或 $P$ 乘上 21 個重量一 Pauli 之一是否屬於 $S$，只對 $s\in\{0,1\}$ 正確。v4_1 在函式開頭加了 `check(s<=1u)`。
- `run()` 結束後的全域變數：`ex,ez` 是 $E$；`er,es` 是 $r,s$；`en,eb,eh0..eh7` 是完整觀測；`ec` 是修正 $C$，低 7 位為 X、高 7 位為 Z。

## 3. 證明鏈

### 步驟 1：每個合法執行都滿足殘餘界限（181 區）

把 1714 種輸入分成 181 個互斥區：initial 區（22 種）以及每個（輪 R、穩定子 K、操作 O）一區（1 或 15 種）。每區都用 CPAchecker 驗證真正的 `run()`，迴圈、分支和 decoder 都保留，證明

$$\mathrm{wt}_{\min}(C E)\le s,\qquad r+s\le 1 .$$

v4_1 每區另外證明 `ec == correction(en,eb,eh0..eh7)`。組合器會獨立重算輸入域，確認覆蓋完整而且互斥。

檔案：`residual/*.c`、`manifest.json`、`results/residual/*`。

### 步驟 2：預算放寬（budget_relaxation）

各次執行有 $r_i+s_i\le1$，所以 $s_i\le1$。由 $\mathrm{wt}_{\min}(CE_i)\le s_i$ 可得 $\mathrm{wt}_{\min}(CE_i)\le 1$。程式檢查：對任意 7 位元 $x,z$ 和 $r,s\le1$，`residual(x,z,s)` 蘊含 `residual(x,z,1)`。

檔案：`budget_relaxation.c`，預期 TRUE。

### 步驟 3：單一殘餘的症狀與奇偶關係（residual_signature）

若 $A=(a_x,a_z)$ 滿足 $\mathrm{wt}_{\min}(A)\le1$，則 $A=T\cdot P$，其中 $T\in S$、$\mathrm{wt}(P)\le1$。$T$ 的 X 部分奇偶為偶、症狀為零，因此 $a_x$ 的奇偶等於 $P$ 的 X 部分的奇偶，而 $P$ 的 X 部分只有兩種可能：沒有 X（奇偶 0、症狀 0），或某一位上的 X（奇偶 1、症狀是 $H$ 的第 $q$ 行，必不為零）。所以

$$\mathrm{parity}(a_x)=[\sigma_x(A)\ne0],\qquad \mathrm{parity}(a_z)=[\sigma_z(A)\ne0].$$

檔案：`residual_signature.c`，預期 TRUE。

### 步驟 4：同觀測 → 同修正（v4 為人工論證，v4_1 改為機器檢查）

v4 依據的是對 scalar.c 的人工閱讀：修正只由 $(n,b,h_0..h_7)$ 決定。v4_1 把這一步拆成兩個機器檢查：

1. 181 區每一區都證明 `ec == correction(en,eb,eh0,...,eh7)`，也就是實際使用的修正等於觀測的函式值。
2. `common_correction.c` 對任意觀測參數連續計算兩次 `correction()`，中間把全部全域輸出變數改成任意值，證明兩次結果相同。也就是說，`correction()` 不依賴觀測以外的任何狀態。

兩者合起來：若 $M(f_1)=M(f_2)=m$，則 $C_1=\texttt{correction}(m)=C_2=:C$。對照組 `common_correction_broken.c` 讓第二次結果也讀被改寫的 `es`，預期 FALSE，確認這個檢查能抓到依賴隱藏狀態的 decoder。

### 步驟 5：消去共同修正並推出 pair 條件（signature_pair）

令 $A_i=CE_i$。因為 $C$ 相同、Pauli 乘法對應 XOR，$A_1\oplus A_2=E_1\oplus E_2=:D$。若 $\sigma(D)=0$，則 $\sigma(A_1)=\sigma(A_2)$；由步驟 3，$A_1$、$A_2$ 的 X 奇偶都由同一個「症狀是否為零」決定，所以兩者相同，$\mathrm{parity}(D_x)=0$，Z 部分同理。症狀為零而且 X、Z 奇偶皆為偶，正好就是 `member(D)`，所以 $D\in S$。

`signature_pair.c` 對任意 $E_1,E_2$ 與任意**共同的** $C$，在 $CE_1$、$CE_2$ 都滿足步驟 3 關係的前提下，檢查 `sy(E1^E2)!=0 || member(E1^E2)`，預期 TRUE。這一步沒有直接使用碼距；它只把 Steane、t=1 需要的代數具體化。我另外在 Python 中窮舉前提允許的全部 4096×4096 組合，沒有反例。

**和 HackMD 碼距論證的關係。** HackMD 的論證是 $\mathrm{wt}(P_1^\dagger P_2)\le s_1+s_2<d$，零症狀加上重量小於碼距，所以必屬穩定子。這個論證適用於一般穩定子碼，但程式並沒有機器檢查它；程式用的是步驟 3、5 這組只對 Steane（CSS、奇偶關係）和 t=1 成立的引理。對目前案例兩者結論相同；要推廣到其他碼，必須改用碼距論證，或依輸入的碼重新產生並驗證對應的引理。

### 對照組

| 檔案 | 預期 | 確認的事 |
|---|---|---|
| pair_bridge_broken.c | FALSE | 拿掉第二次執行的殘餘前提，pair 條件就不成立（例如 $C=I$、$E_1=I$、$E_2=X^{\otimes7}$）。前提不能省略 |
| common_correction_broken.c | FALSE | 依賴隱藏狀態的 decoder 會被抓出 |
| residual_guard_broken.c | FALSE（v4_1） | 對 s=2 呼叫 residual 會被 `check(s<=1u)` 擋下 |
| bitprecise_wrap.c／_bad.c | TRUE／FALSE（v4_1） | 分析確實以 32 位元位元向量建模 |

## 4. 分析設定

全部使用 CPAchecker 4.2.2 安裝目錄中的 `config/bmc.properties`（BMC + 謂詞分析 + 值分析，MathSAT5 5.6.11），`--timelimit 60s`、`cpa.loopbound.maxLoopIterations=128`，bounding assertions 維持預設開啟。在 BMC 中，TRUE 代表展開界限已足夠、沒有遺漏的路徑；若界限不足，結果會是 UNKNOWN，不會是 TRUE。`run()` 的外層迴圈由 `check(n<8u)` 以 assertion 限制，超過容量會報錯，不會被當成假設裁掉。

v4 沒有明確指定編碼；這個 config 鏈裡沒有任何檔案設定 encodeBitvectorAs，所以使用的是 CPAchecker 預設值。v4_1 明確加上 `cpa.predicate.encodeBitvectorAs=BITVECTOR`，並以 bitprecise_wrap 對照組確認；compose.js 也會逐筆核對 result.json 記錄的命令列。

## 5. 已知限制

1. t=1 寫死在模型、`residual()`（只列舉重量一）和輸入域（1714 種）裡。
2. 旗標 decoder 是原 Python 窮舉產生的 288 項表；驗證過程沒有列舉控制流，但建模流程本身仍使用了列舉。
3. 步驟 3、5 的奇偶引理只對 Steane、t=1 成立，與 HackMD 的一般碼距論證不同，碼距論證未經機器檢查。
4. 物理模型（閘的錯誤傳遞、量測基底、旗標電路）只做過三份同源實作（Python、legacy C、scalar C）的差異測試，還沒有用 Stim 之類獨立的穩定子模擬器核對。
5. 直接雙執行的 pair 分析沒有完成：v3 的 `results/pair` 是 47 個 UNKNOWN、134 個 ERROR，其中 133 個是舊執行器的啟動失敗，見 v3 `RESULTS_zh.md` 的 2026-11-22 更正。本證明不改變這些紀錄。
6. 若 decoder 讓殘餘界限不成立，組合式證明就不適用，但這不代表 pair 條件不成立；兩者必須分開回報。

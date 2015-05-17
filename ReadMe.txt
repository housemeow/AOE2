========================================================================
                        About Game Framework 4.6
========================================================================
                            Please refer to 
   http://www.cc.ntut.edu.tw/~wkchen/game/ for more information.
========================================================================

一、簡介

game 4.6是一個開發遊戲程式的平台，其目的是作為一個物件導向程式設計教學的
輔助工具。我在台北科大資工系任教，經常教授物件導向程式設計或其實習課程，
這些課程的教學目標是讓學生熟練程式設計與撰寫的技巧，希望能深植使用C++ 的
能力、熟練VC++的開發環境、熟悉視窗程式設計的元素，以及訓練寫作大型程式的
能力。我在長期的教學經驗中發現，寫再多的小程式，都很難讓學生深刻的體會到
物件的用法與物件的互動，而且無法培養系統的觀念，更遑論開發軟體的能力。因
此，我在實習課程中，要求學生用一整個學期的時間，寫作一個大一點的程式，而
設計視窗遊戲程式，就成為極好的選擇。

我發現透過遊戲設計，可以使程式設計的課程變得比較生動有趣。一般而言，一個
中小型的遊戲(例如小精靈)即已具備小型應用系統的規模，其複雜度足以驗證課堂
上講的程式設計理論，在實作過程中，學生可以體會到，一個應用系統的整體結構
，並能更深入瞭解物件導向設計的原理及精華。當然學生在實作過程中會不斷發現
問題，我則扮演協助學生思考、設計，除錯的角色。過去幾年當中，大多數的學生
都能在課程中得到充分的收穫，也常常有非常專業的作品出現。

然而，要設計一個專業的遊戲，並不是一件很容易的事。其中涉及許多作業系統（
繪圖及音效）的介面操作，與速度控制上的考量，並不是一個學期的課程可以交代
清楚的，而且這些細節，多少會模糊程式實習的焦點，特別是在學生的程式設計能
力還不是很強之前，並不合適。因此，game的平台應運而生，基本上，我的構想是
我自己先將繪圖及音效的問題解決，並且寫成現成的物件，供學生直接引用，那麼
學生們就可以專注在如何設計自己的遊戲應用程式，而透過遊戲設計，就可以學到
很多實作經驗，及解決問題的方法。

在這個第四版的game中，我把遊戲的狀態明確地分成 3個部份，分別是遊戲起始狀
態、遊戲執行狀態及遊戲結束狀態，這使得game的架構更趨近於一個framework，
而不再是一個簡單的library。game各版本之間的主要功能如下：

        第一版 支援DirectDraw繪圖介面                   (game 1.0)
        第二版 增加支援DirectSound音效介面              (game 2.0-2.2)
        第三版 增加支援全螢幕與DirectMusic(MIDI)        (game 3.0-3.1)
        第四版 內建遊戲狀態性的控制                     (game 4.0-4.4)
               可調整的遊戲參數
               新的範例程式
               顯示載入的進度
               支援Visual Studio 2005 (C++)
               局部修正及Bug Fix
               支援Visual Studio 2008 (C++)             (game 4.5)
               用MCI替代DirectMusic                     (game 4.6)
               支援MP3檔音效播放
               支援Windows 7

自第三版開始，我將game的原始程式的版權設定為GPL(詳COPYING檔案)。只要你覺
得有用，我歡迎任何人拿這些原始程式去發展新的遊戲。但是，我希望如果你真的
用這個平台開發出遊戲時，也能讓我知道。如果你發現我的程式有 bug，也請通知
我。

	陳偉凱
	台北科大 資工系副教授
	http://www.ntut.edu.tw/~wkchen

二、使用方法

game4.6可以用在Windows 2000/XP/7。首先你必須有Visual Studio 2008 C++
，並先安裝DirectX SDK (版本視complier而定)，電腦配備則視遊戲的複雜度而定
，一般而言，如果不是很複雜的game，Pentium II或Celeron等級的CPU就足夠了。

要設計一個新的遊戲，基本上就是改寫CGameStateInit、CGameStateRun、以及
CGameStateOver這三個class(在mygame.h及mygame.cpp)，這三個class分別代表
遊戲的起始畫面、遊戲的執行及遊戲結束畫面等三個狀態，在每個狀態中最主要
的動作分為：OnMove()及OnShow()，由OnMove()負責移動遊戲中的物件，再由
OnShow()負責顯示各個物件至螢幕。請參考Game網頁所提供的練習及相關資料:
http://www.cc.ntut.edu.tw/~wkchen/game/。

三、版本差異

1. Game 4.6與Game 4.5的差別
   * 用MCI替代DirectMusic
   * 支援MP3檔音效播放
   * 支援 Windows 7 (因為Windows 7支援DirectMusic的DirectX SDK不相容)
   * Complier 與 Direct X之組合
       * Visual Studio 2008 (C++) 搭配 DirectX February 2010

2. Game 4.5與Game 4.4的差別
   * 支援Visual Studio 2008，不再與VC++6.0相容
   * Complier 與 Direct X之組合
       * Visual Studio 2008 (C++) 搭配 DirectX August 2006

3. Game 4.4與Game 4.3的差別
   * 對Visual Studio 2005，新增一個setup project，以簡化安裝程序。
   * 新增 bitmap 放大或縮小的支援
   * 新增 game_framework namespace，game相關的class都放到此namespace。
   * 新增 bitmap 自檔案載入的支援(以前只能自resource載入)。
   * 新增 ShowInitProgress(percent) 顯示載入圖形及音效的進度。
   * Complier 與 Direct X之組合
       * Visual Studio 2005 (C++) 搭配 DirectX August 2006
       * VC++6.0 搭配 DirectX 8.x


4. Game 4.3與Game 4.2的差別
   * 支援Visual Studio 2005 (C++); 不再支援Visual Studio .net 2003。
   * Move()改為OnMove(); Show()改為OnShow()。
   * 新增ENABLE_GAME_PAUSE選項。
   * 修復電源suspend再啟動後，音效失靈的問題。
   * Complier 與 Direct X之組合
       * Visual Studio 2005 (C++) 搭配 DirectX August 2006
       * VC++6.0 搭配 DirectX 8.x

5. Game 4.2與Game 4.1的差別
   * 重寫範例程式。
   * 同時支援Visual Studio .net 2003 (C++) 與 VC++6.0。
   * 局部修正及Bug Fix。
   * 新增MouseMove對應程式。
   * Complier 與 Direct X之組合
       * Visual Studio .net 2003 (C++) 搭配 DirectX 8.x
       * VC++6.0 搭配 DirectX 8.x

6. Game 4.1與Game 3.1的差別
   * 內建遊戲狀態性的控制。
   * 可調整的遊戲參數。
   * Complier 與 Direct X之組合
       * VC++6.0 搭配 DirectX 8.x

7. Game 3.1與Game 2.2的差別
   * 支援全螢幕。
   * 支援MIDI。
   * 增加了一個動畫的物件。
   * 修正了一些 bug。
# Alternate
Visual Studio 2019 C++ Sample Solution

これは、Visual Studio 2019 C++のサンプルソリューションです。
Gitも初心者です。Visual Studioは昔使っていました。最新情報のキャッチアップと昔の手法を新しい技術で実装するとどうなるのかの研究の下地に使いたいと思っています。

## ConsoleDriver
コマンドラインベースでDLLを実行させるスターターの役目を担います。

## MiddleLibrary
呼び出された後、システム全体を統制する作業を担います。

### WorkerTemplate
大域制御用の仕組みを実装します。一つは各メソッドにスレッド排他制御用の仕組みとステータスの遷移を実装し、
重要なロジックは外部からラムダ式で挿入する方法を取りました。

## WindowsLibrary
Windows APIをある程度クラス化してまとめています。Windowsの場合以下の項目である程度まとまりそうです。

- WindowsLibrary
    - CriticalSection
    - Exception
      - InvalidArgumentException
      - RuntimeException
    - FileUtility
    - HandleLibrary
        - Console
        - Diagnostics
        - HeapMemory
        - ReadWriteHandleLibrary
            - File
              - TransactionFile
            - NamedPipe
        - SharedMemory
        - TransactionFileUtility
        - WaitableHandleLibrary
            - Event
            - Mutex
            - Thread
            - WatchDogTimer
    - ICallback
    - ITimeup
    - LogFile
    - Logger
    - Pipe
    - Process
    - QueryPerformance
    - RingBuffer
    - SocketLibrary
        - SocketBuilder
        - TcpConnector
        - UdpConnector
    - TString
    - Utility
    - VirtualMemory


できる限りWindowsのAPI(つまりカーネルDLL)だけ使うようにします。またカーネルコールは昔ながらのハンガリアン記法を使用しますが、ライブラリ提供時点では標準的な変数にしようと思っています。
STLやBOOSTはMiddleLibraryより上位で使うようにして、ここではクラスにWindows APIが便利に使える点だけを求めてみます。

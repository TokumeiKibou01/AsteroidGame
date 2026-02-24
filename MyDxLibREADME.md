# MyDxLib

## 概要
* ゲームを作る際のクラス等をまとめたテンプレートです。

## 使用方法
1.　git clone https://github.com/TokumeiKibou01/MyDxLib.git と打つ。<br/>
2.　VisualStudioでクローンしたプロジェクトを開く。<br>
3.　クラスを拡張して、ゲームを作る。

## 使用ライブラリ
* DxLib

## ファイルの説明
「AppMain.cpp」- メインの関数。<br>

### 管理
「ObjectManager.cpp/h」- オブジェクトを管理するクラス。<br>
「SceneManager.cpp/h」- シーンを管理するクラス。<br>

### ライブラリー
「Location2D.cpp/h」- 2D座標を扱うクラス。<br>
「Vector2D.cpp/h」 - 2Dベクトルを扱うクラス。<br>
#### デバック
「DebugWindow/ImGUI」- デバックウインドウ用のImGUI（※推奨）。<br>
「DebugWindow/Win32」- デバックウインドウ用のWin32API（※非推奨）。<br>

### オブジェクト
「Base2DObject.cpp/h」- 2Dオブジェクトの基底クラス。<br>
「BoxObject.cpp/h」 - 四角形を描画するクラス（※DxLib::DrawBoxを使用）。<br>

### シーン
「BaseScene.cpp/h」- シーンの基底クラス。<br>
「BootScene.cpp/h」- 最初に呼び出されるシーン。<br>

### リソース（画像・動画等）
なし

### その他
「.editorconfig」- C++のコーディングスタイルを設定するファイル。

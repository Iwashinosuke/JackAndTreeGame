Dockerコンテナを用いて、実機環境を汚さずに環境構築できます。

ビルドする場合は、このdockerディレクトリ上にて

$ docker-compose up

を実行してください。

-注
WindowsでDockerコンテナを用いる場合、GUIアプリケーションを実行するためにWSLgの経由が強く推奨されます。
そのため、Dockerコンテナのビルド・起動はWSL上で行ってください。

(Windows上で直にコンテナを作成すると、ALSAやWaylandなどのドライバが機能しないことがあります)

想定環境:
Dockerベースイメージ: Ubuntu 22.04 LTS以降
WSL2: Ubuntu 22.04 LTS以降(本ファイル作成時 Ubuntu 24.04.1 LTS)
mkdir .\build
mkdir .\build\html
emcc Dilgine\Dilgine\Source\main.cpp -sUSE_SDL=2 -sLLD_REPORT_UNDEFINED -IDilgine\Dilgine\Header -o .\build\html\index.html
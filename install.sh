s="[Desktop Entry]\nName=海天鹰PDF\nComment=海天鹰 PDF Reader\nExec=`pwd`/HTYPDF %u\nIcon=`pwd`/HTYPDF.png\nPath=`pwd`\nTerminal=false\nType=Application\nMimeType=application/pdf;\nCategories=Office;"
echo -e $s > HTYPDF.desktop
cp `pwd`/HTYPDF.desktop ~/.local/share/applications/HTYPDF.desktop

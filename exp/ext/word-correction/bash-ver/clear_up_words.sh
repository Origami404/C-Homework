cat words.txt | tr "/" " " | tr -cd "a-zA-Z0-9 \n"

void displayText(String text, int timeDelay, RGB color);
void displayChar(bool SELECTED_CHAR[CS][CS], int timeDelay, RGB color);
void selectAndDisplayChar(char selectedChar, int timeDelay, RGB color);

void displayText(String text, int timeDelay, RGB color)
{ 
  int len = text.length();
  for(int i = 0; i<len; i++)
    selectAndDisplayChar(text.charAt(i), timeDelay, color);
    
   pixels.clear();
   pixels.show();
}

void displayChar(bool SELECTED_CHAR[CS][CS], int timeDelay, RGB color)
{
    for(int y = 1; y<=CS; y++)
    {
        for(int z = 1; z<=CS; z++)
          for(int x = 1; x<=CS; x++)
            if(SELECTED_CHAR[z-1][x-1] == 1)
              setDiode(x, y, z, color);

          pixels.show();
          pixels.clear();
          delay(timeDelay);
    }
}

void selectAndDisplayChar(char selectedChar, int timeDelay, RGB color)
{
    if (selectedChar == 'A')
        displayChar(A, timeDelay, color);
    else if (selectedChar == 'B')
        displayChar(B, timeDelay, color);
    else if (selectedChar == 'C')
        displayChar(C, timeDelay, color);
    else if (selectedChar == 'D')
        displayChar(D, timeDelay, color);
    else if (selectedChar == 'E')
        displayChar(E, timeDelay, color);
    else if (selectedChar == 'F')
        displayChar(F, timeDelay, color);
    else if (selectedChar == 'G')
        displayChar(G, timeDelay, color);
    else if (selectedChar == 'H')
        displayChar(H, timeDelay, color);
    else if (selectedChar == 'I')
        displayChar(I, timeDelay, color);
    else if (selectedChar == 'J')
        displayChar(J, timeDelay, color);
    else if (selectedChar == 'K')
        displayChar(K, timeDelay, color);
    else if (selectedChar == 'L')
        displayChar(L, timeDelay, color);
    else if (selectedChar == 'M')
        displayChar(M, timeDelay, color);
    else if (selectedChar == 'N')
        displayChar(N, timeDelay, color);
    else if (selectedChar == 'O')
        displayChar(O, timeDelay, color);
    else if (selectedChar == 'P')
        displayChar(P, timeDelay, color);
    else if (selectedChar == 'Q')
        displayChar(Q, timeDelay, color);
    else if (selectedChar == 'R')
        displayChar(R, timeDelay, color);
    else if (selectedChar == 'S')
        displayChar(S, timeDelay, color);
    else if (selectedChar == 'T')
        displayChar(T, timeDelay, color);
    else if (selectedChar == 'U')
        displayChar(U, timeDelay, color);
    else if (selectedChar == 'V')
        displayChar(V, timeDelay, color);
    else if (selectedChar == 'W')
        displayChar(W, timeDelay, color);
    else if (selectedChar == 'X')
        displayChar(X, timeDelay, color);
    else if (selectedChar == 'Y')
        displayChar(Y, timeDelay, color);
    else if (selectedChar == 'Z')
        displayChar(Z, timeDelay, color);
    else if (selectedChar == '0')
        displayChar(ZERO, timeDelay, color);
    else if (selectedChar == '1')
        displayChar(ONE, timeDelay, color);
    else if (selectedChar == '2')
        displayChar(TWO, timeDelay, color);
    else if (selectedChar == '3')
        displayChar(THREE, timeDelay, color);
    else if (selectedChar == '4')
        displayChar(FOUR, timeDelay, color);
    else if (selectedChar == '5')
        displayChar(FIVE, timeDelay, color);
    else if (selectedChar == '6')
        displayChar(SIX, timeDelay, color);
    else if (selectedChar == '7')
        displayChar(SEVEN, timeDelay, color);
    else if (selectedChar == '8')
        displayChar(EIGHT, timeDelay, color);
    else if (selectedChar == '9')
        displayChar(NINE, timeDelay, color);
    else if(selectedChar == ' ')
    {
         pixels.clear();
         pixels.show();
         delay(timeDelay*8);
    }
        
}

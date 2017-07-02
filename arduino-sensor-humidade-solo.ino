#include <U8glib.h>
#define QTD_SENSORES 4
int valores[QTD_SENSORES];

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  u8g.setColorIndex(1);
  u8g.setFont(u8g_font_5x7);
}
 
void loop()
{
  valores[0] = porcentagem(analogRead(A0));
  valores[1] = porcentagem(analogRead(A1));
  valores[2] = porcentagem(analogRead(A2));
  valores[3] = porcentagem(analogRead(A3));
  
  u8g.firstPage();  
  do
  { 
    desenhar();
  } while(u8g.nextPage());
  
  delay(100);
}

int porcentagem(int leitura)
{
  return map(leitura, 1023, 420, 0, 100);
}

void desenhar() 
{
  int sizeWidth = 25;
  int sizeHeight = 55;
  int posX = 5;
  
  for (int i = 0; i < QTD_SENSORES; i++)
  {
    escreverNumeroEmbaixoDoBox(i, posX);

    //Desenhar Contorno do Box
    u8g.drawRFrame(posX, 0, sizeWidth, sizeHeight, 0);

    if(valores[i] > 0)
    {
      int humidade = sizeHeight - map(valores[i], 100, 0, 0, sizeHeight);

      if(humidade > 0)
      {
        u8g.drawBox(posX, sizeHeight - humidade, sizeWidth, humidade);
      }
    }
    
    posX += sizeWidth + 5;
  }
}

void escreverNumeroEmbaixoDoBox(int i, int posX)
{
  char numero[2];
  String str = String(i + 1);
  str.toCharArray(numero, 2);
  u8g.drawStr(posX + 8, 63, numero);
}

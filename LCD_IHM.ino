
#include <LiquidCrystal.h>
#include <EEPROM.h>

#define SELECT  1
#define LEFT    2
#define UP      3
#define DOWN    4
#define RIGHT   5

// --- Hardware do LCD ---
LiquidCrystal lcd(8,  //RS no digital 8
                   9,  //EN no digital 9
                   4,  //D4 no digital 4
                   5,  //D5 no digital 5
                   6,  //D6 no digital 6
                   7); //D7 no digital 7
                   
String MenuMotor[4] = { "Motor 1", "Motor 2", "Sair", " "};
int menuMotorIndice = 0;
int valorProducao = 100;

void setup() {
  lcd.begin(16, 2);
  textoInicializar();
  delay(2000);
  
  menuPrincipal();
}

void loop() {
 if (getClique() == SELECT)
    menuMotor();
}
//lcd.print(EEPROM.read(0));
//EEPROM.write(0, 0);

void menuMotor()
{
  menuMotorIndice = 0;
  menuMotor_imprime();
  while(true)
  {
    if (getClique() == DOWN)
    {
      if(menuMotorIndice < 2)
      {
        menuMotorIndice +=1;
        menuMotor_imprime();
      }        
    }
  
    if (getClique() == UP)
    {
       if(menuMotorIndice > 0)
      {
        menuMotorIndice -=1;
        menuMotor_imprime();
      }
    }
  
    if (getClique() == SELECT)
    {
      switch(menuMotorIndice)
      {
        //case 0:
       //   menuMotor1;
       // break;
       // case 1:
       //   menuMotor2;
       // break;
        case 2:
          menuPrincipal();
          return;
        break;
      }
    }
  }
}
void limparLinha(int line)
{
  lcd.setCursor(0, line - 1);
  lcd.print("                ");
  lcd.setCursor(0, line - 1);
}

void atualizaProducao(int p)
{
  limparLinha(2);
  lcd.print("Producao:" + String(p));
  delay(50);
}

void menuMotor_imprime()
{
  switch(menuMotorIndice)
  {
    case 0:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("-> " + MenuMotor[menuMotorIndice]);
      lcd.setCursor(0,1);
      lcd.print("   " + MenuMotor[menuMotorIndice + 1]);
    break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("-> " + MenuMotor[menuMotorIndice]);
      lcd.setCursor(0,1);
      lcd.print("   " + MenuMotor[menuMotorIndice + 1]);
    break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("-> " + MenuMotor[menuMotorIndice] + menuMotorIndice);
      lcd.setCursor(0,1);
      lcd.print("   " + MenuMotor[menuMotorIndice + 1]);
    break;
  }
  delay(500);
}


int getClique()
{
  //Sem botao: Retorna 0
  //Botao: Select -> Retorna 1
  //Botao: Left -> Retorna 2
  //Botao: Up -> Retorna 3
  //Botao: Down -> Retorna 4
  //Botao: Right -> Retorna 5
  int valor = analogRead(0);

  if(valor > 718 && valor < 729) //Select 723
  {
    return 1;
  }else if (valor > 475 && valor < 485) //Left 480
  {
    return 2;
  }else if (valor > 128 && valor < 137) //Up 132
  {
    return 3;
  }else if (valor > 300 && valor < 315) //Down 307
  {
    return 4;
  }else if (valor > -5 && valor < 5) //Right 0
  {
    return 5;
  }else
    return 0;
}

void textoInicializar()
{
  lcd.setCursor(0, 0);
  lcd.print("    CLARAMAQ    ");
  lcd.setCursor(0, 1);
  lcd.print("   Automacao   ");
}

void menuPrincipal()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    CLARAMAQ    ");
  lcd.setCursor(0, 1);
  lcd.print("Producao:" + valorProducao);
}
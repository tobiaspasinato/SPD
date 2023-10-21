#define A 7
#define B 8
#define C 9
#define D 10
#define E 11
#define F 12
#define G 13
#define aumenta 6
#define reduce 5
#define reset 4

#define UNIDAD A5
#define DECENA A4
#define APAGADOS 0


int bajaPrevia=1;
int subePrevia=1;
int resetPrevia=1;
int contadorDigito=0;

void setup()
{
  pinMode(reduce, INPUT_PULLUP);
  pinMode(aumenta, INPUT_PULLUP);
  pinMode(reset, INPUT_PULLUP);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(UNIDAD, OUTPUT);
  pinMode(DECENA, OUTPUT);
  digitalWrite(UNIDAD,0);
  digitalWrite(DECENA,0);
  Serial.begin(9600);
}


void loop() {
  int precionado = teclaPrecionado();

  
    if (precionado == aumenta) {
      // Incrementar el número
      contadorDigito++;
      if (contadorDigito > 99)
        contadorDigito = 0;
    }
    else if (precionado == reset) {
      // Resetear el número a 0
      contadorDigito = 0;
    }
    else if (precionado == reduce) 
    {
      contadorDigito--;
      if(contadorDigito<0)
        contadorDigito=99;
    }
  

  muestraNumeros(contadorDigito);
}



//funcion para prender los displays
void prendeUnNumero(int digit)
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  switch (digit)
  {
    case 1:
    {
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      break;
    }
    case 2:
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(G, HIGH);
      break;
    }

    case 3:
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(G, HIGH);
      break;
    }
    case 4:
    {
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    }

    case 5:
    {
      digitalWrite(A, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    }
    case 6:
    {
      digitalWrite(A, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    }

    case 7:
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      break;
    }
    case 8:
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    } 
    case 9:
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    } 

    case 0:
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      break;
    }


  }


}



void cambiaDigito(int digito) // prende o apaga un displey "una vez uno, una vez otro : decena ó unidad"
{
  if (digito == UNIDAD)
  {
    digitalWrite(UNIDAD, 0); // pongo el comun de unidad en 0 (enciende)
    digitalWrite(DECENA, 1); // pongo el comun de decena en 1 (no enciende)
    delay(30);
  }
  else if (digito == DECENA)
  {
    digitalWrite(UNIDAD, 1);// pongo el comun de unidad en 1 (no enciende)
    digitalWrite(DECENA, 0);// pongo el comun de decena en 0 ( enciende)
    delay(100);

  }
  else
  {
    digitalWrite(UNIDAD, 1);// pongo el comun de unidad en 1 (no enciende)
    digitalWrite(DECENA, 1);// pongo el comun de unidad en 1 (no enciende)

  }

}



void muestraNumeros(int contador) //enciende los displeys
{
  cambiaDigito(APAGADOS);
  prendeUnNumero(contador/10);// divido el numero por 10 y tomo elvalor sin el decimal. El cociente es la decena 
  cambiaDigito(DECENA);// muestro el resultado de la cuenta anterior en la decena
  cambiaDigito(APAGADOS);
  prendeUnNumero(contador - 10*((int)contador/10));// divido el numero por 10 y tomo el valor sin el decimal
  // luego multiplico el cociente por 10 ahora el producto lo resto del numero . La diferencia es la unidad
  cambiaDigito(UNIDAD);  // muestro el resultado de la cuenta anterior en la unidad
}


int teclaPrecionado(void)// informa que pulsador se preciono, devuelve el numero que se preciono
{ 
	
  	int sube = digitalRead(aumenta); // devuelve 0 si presiono, 1 si no presiono
  	int baja = digitalRead(reduce);
	int reseteo = digitalRead(reset);
    	
  		if(sube==0 && sube != subePrevia)
        {
          subePrevia = sube;
  		  return aumenta;
        }
  
    	if(baja==0 && baja != bajaPrevia)
        {
          bajaPrevia = baja;
  		  return reduce;
        }
  
      	if(reseteo==0 && reset != resetPrevia)
        {
          resetPrevia = reseteo;
  		  return reset;
        }
  			subePrevia = 1;
    		bajaPrevia = 1;
    		resetPrevia = 1;
  
 return 0; //o no presione ninguna tecla, o presione una que estaba presionada
 
}
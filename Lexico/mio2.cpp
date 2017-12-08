#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <stack>
using namespace std; 
///COMPILAR ASI ---->   g++ -std=c++0x mio2.cpp -o a

char caracter = ' ';
vector<char> listarecorrido;
vector<pair < string ,int > > lista; 
			// token 		LEXEMAS   linea
vector<pair< string ,  pair < string ,int > > > lista_tokens; 
vector<pair< string ,  pair < string ,int > > > lista_errores; 
vector<pair< string ,  pair < string ,int > > > lista_errores_sintacticos; 
vector<pair< string ,  pair < string ,int > > > lista_errores_semanticos; 
int linea_actual=0;
//vector<pair< string ,  pair < string ,int > > > tabla_simbolos; 

struct campos {
        string token;
        string lexema;
        int linea;
        string tipo;
        string valor;
        int tamanho;
        basic_string<char>* direcccion;
        int dir;

};
struct atributos {
        string token;//terminal
        string type;
        string value;
        string lexema;
        int tamanho;
        int dir;
        basic_string<char>* direcccion;
        string lugar;
        string comienzo;
        string despues;
        
        string codigo;
        int pos;

};
struct terminales {
        vector< atributos >  PC_clave_Include;
        vector< atributos >  PC_Decl_int;
        vector< atributos >  PC_Decl_float;
		vector< atributos >  PC_Decl_double;
		vector< atributos >  PC_Decl_bool;
		vector< atributos >  PC_Decl_char;
		vector< atributos >  PC_clave_main;
		vector< atributos >  Parentesis_Abierto;
		vector< atributos >  Parentesis_Cerrado;
		vector< atributos >  Llave_Abierta;
		vector< atributos >  Llave_Cerrada;
		vector< atributos >  Corchete_Abierto;
		vector< atributos >  Corchete_Cerrado;
		vector< atributos >  Punto_Coma;
		vector< atributos >  Coma;
		vector< atributos >  OP_Asignacion_Igual;
		vector< atributos >  PC_Clave_return;
		vector< atributos >  Num_Entero;
		vector< atributos >  OP_Logico_And;
		vector< atributos >  OP_Logico_Or;
		vector< atributos >  OP_Relacional_Menor;
		vector< atributos >  OP_Relacional_Mayor;
		vector< atributos >  OP_Relacional_Mayor_Igual;
		vector< atributos >  OP_Relacional_Menor_Igual;
		vector< atributos >  OP_Relacional_Igual;
		vector< atributos >  OP_Relacional_Diferente;
		vector< atributos >  OP_Aritmetico_Suma;
		vector< atributos >  OP_Aritmetico_Resta;
		vector< atributos >  OP_Aritmetico_Mult;
		vector< atributos >  OP_Aritmetico_Div;
		vector< atributos >  OP_Aritmetico_Mod;
		vector< atributos >  ID;
		vector< atributos >  PC_Clave_if;
		vector< atributos >  PC_Clave_while;
        vector< atributos >  PC_Clave_else;
        vector< atributos >  Num_Flotante;
        vector< atributos >  $;
};
stack<atributos> pila; 
map< string , campos > tabla_de_simbolos;
///NO TERMINAL      TERMINAL  PRODUCCIoN 
map< string, pair <atributos , terminales> > tabla_sintactica;


void metodoArchivo() {//Lee caracter por caracter del Archivo .txt
    //int linea = 0;
    ifstream fichero; //variable fichero para leer los datos
    fichero.open(("archivo_lenguaje.txt"));
    //fichero.get(caracter);
    string frase,token;
    int line=1;
    int linea_abre=1;

    if (fichero.fail()) {// si fichero no falla coge un letra dle fichero
        cout << "Error al abrir el archivo_lenguaje.txt" << endl;

    } 
    else {
    	int salta_linea=0;
        int buscar_cierre=0;
        int cadena=0;
        string cadenita;

        while (!fichero.eof()) {//mientras fichero no llegue al final
        	//listarecorrido.push_back(caracter);

            //fichero.get(caracter);
            getline(fichero,frase);
            
            int a=-1,b=0;
            for(int i =0;i<frase.size();i++)
            {  
            	if(a==-1 and frase[i]=='"') 
            		a=i;
            }
            for(int i =a+1;i<frase.size();i++)
            { 	//cout<<frase[i]<<endl;   	
            	if (frase[i]=='"') 
            		{  
            			b=i;
            			break;
            		}

            }
            if(a!=-1)
            {   //cout<<a<<" , "<<b<<endl;
            	//cout<<frase.substr(a,b-a+1)<<endl;
                //cadenita=frase.substr(a,b-a+1);
            	lista.push_back(make_pair(frase.substr(a,b-a+1),line));
            	frase=frase.substr(0,a-1)+" "+frase.substr(b+1,frase.size()-1-(b+1));
            }
            //cout<<"la frase: "<<frase<<endl;
            ///Tokens
            istringstream iss(frase);
			while(getline(iss,token,' '))
			{
			    //if(token!= " " and token!= "\t")
			    ///OBVIAR COMENTARIOS
				for(int  i = 0; token[i] != 0;++i)
				{
        			if(token[i] == '/' and token[i+1] == '/')
        			{
        				salta_linea=1;
        			}
        			if(token[i] == '/' and token[i+1] == '*')
        			{
        				salta_linea=2;
        				buscar_cierre=2;
        				linea_abre=line;
        			}
        			if(token[i] == '*' and token[i+1] == '/')
        			{
        				buscar_cierre=1;
        				
        			}
        			if(token[i] == '\n')
        			{
        				salta_linea=1;
        				
        			}
        			       			
        		}
           			//	return;//cout<<token[i]<<endl;
               
				if(cadena==0 and salta_linea==0 and buscar_cierre==0 and token!="" )
				{   
			   	 	
			   	 	//cout<< line <<"toki: "<<  token << endl;
            		if(b==0)lista.push_back(make_pair(token,line));
				}
				if(buscar_cierre==1)buscar_cierre=0;
			    //lista.push_back(ptr);
			    //ptr = strtok(NULL, " ");
			}
			line++;
			salta_linea=cadena=0;


        }
        	if(buscar_cierre!=0)
				lista_errores.push_back(make_pair("ERROR: Comentario no cerrado", make_pair(token ,linea_abre)));
    }
    fichero.close();
}

vector<pair < string ,int >> lis;
void validacion(pair < string ,int > palabra)
{	
	lis.push_back(palabra);
}
///Tipo de errors simbolos que no pertenecen al lenguaje    comentarios
/// tabla de simbolos 
void validacion2(pair < string ,int > palabra)
{	//cout<<"|"<<palabra.first<<"|"<<palabra.first.size()<<endl;
	regex integer("(\\+|-)?[[:digit:]]+");
	regex flotante("(\\+|-)?[[:digit:]]+.[[:digit:]+]+|[[:digit:]+]");
	regex word("[a-zA-Z]+?[|0-9|a-zA-Z]*");
	regex includes("#include( [a-zA-Z]+|[a-zA-Z]+(.h)?)");
	string cosita=palabra.first;
	int no_entra=0;
	//cout<<"cosita"<<cosita<<endl;
	if(palabra.first.size()==1)
	{   //cout<<"ESPACIO"<<endl;
		//cout<<"posible_salto:"<<palabra.first[0]<<endl;
		int asc=(char)palabra.first[0];
	    //cout<<"ESPACIOO:"<<asc<<"|"<<endl;
		if(asc==13 ) {
			no_entra=1;
		}
	}
	if(no_entra==0)
	{
		//cout<<"VALIDA"<<endl;
		string aux="";
		for(int i=0;i<palabra.first.size();i++)
		{
			
			int asc=(char)palabra.first[i];
			if(asc!=13)
				aux+=palabra.first[i];

			//if (asc ==)
		}
		//cout<<"PALABRA"<<palabra.first[0]<<endl;
		palabra.first=aux;
		if(palabra.first =="" or palabra.first ==" " or palabra.first =="\n" ) ;
		else if (palabra.first[0] =='"')
			lista_tokens.push_back(make_pair("Cadena", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="main")
			lista_tokens.push_back(make_pair("PC_clave_main", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="bool")
			lista_tokens.push_back(make_pair("PC_Decl_bool", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="char")
			lista_tokens.push_back(make_pair("PC_Decl_char", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="float")
			lista_tokens.push_back(make_pair("PC_Decl_float", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="double")
			lista_tokens.push_back(make_pair("PC_Decl_double", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="int")
			lista_tokens.push_back(make_pair("PC_Decl_int", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="long")
			lista_tokens.push_back(make_pair("PC_Decl_long", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="else")
			lista_tokens.push_back(make_pair("PC_Clave_else", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="for")
			lista_tokens.push_back(make_pair("PC_Clave_for", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="if")
			lista_tokens.push_back(make_pair("PC_Clave_if", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="return")
			lista_tokens.push_back(make_pair("PC_Clave_return", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="while")
			lista_tokens.push_back(make_pair("PC_Clave_while", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="+")
			lista_tokens.push_back(make_pair("OP_Aritmetico_Suma", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="-")
			lista_tokens.push_back(make_pair("OP_Aritmetico_Resta", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="*")
			lista_tokens.push_back(make_pair("OP_Aritmetico_Mult", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="/")
			lista_tokens.push_back(make_pair("OP_Aritmetico_Div", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="%")
			lista_tokens.push_back(make_pair("OP_Aritmetico_Mod", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="=")
			lista_tokens.push_back(make_pair("OP_Asignacion_Igual", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="+=")
			lista_tokens.push_back(make_pair("OP_Asignacion_Mas_Igual", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="-=")
			lista_tokens.push_back(make_pair("OP_Asignacion_Menos_Igual", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="*=")
			lista_tokens.push_back(make_pair("OP_Asignacion_Por_Igual", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="/=")
			lista_tokens.push_back(make_pair("OP_Asignacion_Entre_Igual", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="==")
			lista_tokens.push_back(make_pair("OP_Relacional_Igual", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="<")
			lista_tokens.push_back(make_pair("OP_Relacional_Menor", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first ==">")
			lista_tokens.push_back(make_pair("OP_Relacional_Mayor", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="<=")
			lista_tokens.push_back(make_pair("OP_Relacional_Menor_Igual", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first ==">=")
			lista_tokens.push_back(make_pair("OP_Relacional_Mayor_Igual", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="!=")
			lista_tokens.push_back(make_pair("OP_Relacional_Diferente", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="&&")
			lista_tokens.push_back(make_pair("OP_Logico_And", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="||")
			lista_tokens.push_back(make_pair("OP_Logico_Or", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="!")
			lista_tokens.push_back(make_pair("OP_Logico_Negacion", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="{")
			lista_tokens.push_back(make_pair("Llave_Abierta", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="}")
			lista_tokens.push_back(make_pair("Llave_Cerrada", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="(")
			lista_tokens.push_back(make_pair("Parentesis_Abierto", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first==")")
			lista_tokens.push_back(make_pair("Parentesis_Cerrado", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="[")
			lista_tokens.push_back(make_pair("Corchete_Abierto", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="]")
			lista_tokens.push_back(make_pair("Corchete_Cerrado", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first ==";")
			lista_tokens.push_back(make_pair("Punto_Coma", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first ==",")
			lista_tokens.push_back(make_pair("Coma", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="++")
			lista_tokens.push_back(make_pair("OP_Mas_Mas", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="--")
			lista_tokens.push_back(make_pair("OP_Menos_Menos", make_pair(palabra.first ,palabra.second)));
		else if(regex_match(palabra.first,integer))
			lista_tokens.push_back(make_pair("Num_Entero", make_pair(palabra.first ,palabra.second)));	
		else if(regex_match(palabra.first,flotante))
			lista_tokens.push_back(make_pair("Num_Flotante", make_pair(palabra.first ,palabra.second)));
		else if(regex_match(palabra.first,includes))
			lista_tokens.push_back(make_pair("PC_clave_Include", make_pair(palabra.first ,palabra.second)));
		else if(regex_match(palabra.first,word))
			{
				lista_tokens.push_back(make_pair("ID", make_pair(palabra.first ,palabra.second)));
				//cout<<"PALABRA"<<palabra.first<<endl;
			}
		else 
			{   //cout<<"NO PERTENECE: |"<<palabra.first<<"| "<<palabra.first.size()<<endl;
				//lista_tokens.push_back(make_pair("ERROR", make_pair(palabra.first ,palabra.second)));
				lista_errores.push_back(make_pair("ERROR: No pertenece al lenguaje", make_pair(palabra.first ,palabra.second)));
			}
		//else 
		//	cout<<"fallo "<<palabra.first<<endl;
			//lista_tokens.push_back(make_pair("ID", make_pair(palabra.first ,palabra.second)));
	}
}
void separar (pair < string ,int > palabra)
{   string palabra1,palabra2, signo;
	int j;
	for(j=0;j<palabra.first.size();j++)
	{   //cout<<"aquitoy "<< palabra.first<<"  "<<j<<endl;
		if(palabra.first[j]=='"')
		{   
			validacion(make_pair(palabra.first,palabra.second));
			break;
		}
		else if(palabra.first[j]==';' or palabra.first[j]=='(' or palabra.first[j]==')' or palabra.first[j]=='{' or palabra.first[j]=='}'
			or palabra.first[j]=='[' or palabra.first[j]==']'
			or palabra.first[j]=='%' )
		{
  			
  			if(palabra.first.size()!=1)
			{ 
				//cout<<"ENTRA :  "<<palabra.first<<"es"<<palabra.first.size()<<endl;
				palabra1=palabra.first.substr(0,j);//cout<<"pala1"<<palabra1<<endl;
				if (palabra1.size()>=1)separar(make_pair(palabra1,palabra.second));
				signo= palabra.first.substr(j,1);//cout<<"signo"<<signo<<endl;
				if (signo.size()>=1)validacion(make_pair(signo,palabra.second));
				palabra2= palabra.first.substr(j+1,palabra.first.size()-j-2);//cout<<"pala2"<<palabra2<<endl;
				if (palabra2.size()>=1) separar(make_pair(palabra2,palabra.second));
				//cout<<"HEREEE:  "<<palabra.first<<"="<<palabra1<<","<<signo<<","<<palabra2<<endl;
				break;
  			}
  			else validacion(make_pair(palabra.first,palabra.second));
  			break;
  				
		}
		else if(palabra.first[j]=='+' or palabra.first[j]=='-' or palabra.first[j]=='*' or palabra.first[j]=='/' or palabra.first[j]=='=' or palabra.first[j]=='!'
			or palabra.first[j]=='<' or palabra.first[j]=='>' )
		{   int cero=0;
  			if(palabra.first[j+1]=='=')
  				cero=1;
  				//cout<<"GG "<<palabra.first<<endl;
  			
				palabra1=palabra.first.substr(0,j);//cout<<"PAlabra1 "<<palabra1<<endl;
				if (palabra1.size()>0)separar(make_pair(palabra1,palabra.second));
				signo= palabra.first.substr(j,1+cero);//cout<<"Signo "<<signo<<endl;
				if (signo.size()>0)validacion(make_pair(signo,palabra.second));
				palabra2= palabra.first.substr(j+1+cero,palabra.first.size()-j-1-cero);//cout<<"PAlabra2 "<<palabra2<<endl;
				if (palabra2.size()>0) separar(make_pair(palabra2,palabra.second));
  			break;
  				
		}
		else if((palabra.first[j]=='=' and palabra.first[j+1]=='=') 
			 or (palabra.first[j]=='&' and palabra.first[j+1]=='&')
			 or (palabra.first[j]=='|' and palabra.first[j+1]=='|')
			 or (palabra.first[j]=='+' and palabra.first[j+1]=='+')  
			 or (palabra.first[j]=='-' and palabra.first[j+1]=='-')  )
		{   int cero=1;

				palabra1=palabra.first.substr(0,j);
				if (palabra1.size()>0)separar(make_pair(palabra1,palabra.second));
				signo= palabra.first.substr(j,1+cero);
				if (signo.size()>0)validacion(make_pair(signo,palabra.second));
				palabra2= palabra.first.substr(j+1+cero,palabra.first.size()-j-2);
				if (palabra2.size()>0) separar(make_pair(palabra2,palabra.second));
  			break;
		}
		/*else if
		{   //cout<<"ICI:  "<<palabra.first<<endl;
			validacion(make_pair(palabra.first,palabra.second));
			break;
		}*/

	}
	//cout<<"tamaño"<<j<<" compare "<<palabra.first.size()-1<<endl;
	if(j==palabra.first.size()and j!=0) {
			//cout<<"googogogog   "<<palabra.first<<endl;
		validacion(make_pair(palabra.first,palabra.second));
	}

}

// te encuentra auspicios 
// contactos 
void tokens()
{  
	for(int i=0; i<lista.size();i++)
	{   
		//cout<<"Algo "<<lista[i].first<<endl;
		separar(lista[i]);
		
  	//cout<<lista[i].second<<"\t"<<lista[i].first<<endl;
		//cout<<"palabra: "<<palabra<<"  signo:"<<signo<<endl;
	}
	for(int i=0; i<lis.size();i++)
	{   //cout<<"Algos "<<lista[i].first<<endl;
		validacion2(lis[i]);
		
  	//cout<<lista[i].second<<"\t"<<lista[i].first<<endl;
		//cout<<"palabra: "<<palabra<<"  signo:"<<signo<<endl;
	}

}
void inicializa_tabla_simbolos()
{
  for(int i=0; i<lista_tokens.size();i++)
  {
   campos a;
   a.token=lista_tokens[i].first; 			//cout<<"muere aqui fuera "<<lista_tokens[i].first<<endl;
   a.linea=lista_tokens[i].second.second;	//cout<<"muere aqui fuera2 "<<lista_tokens[i].second.second<<endl;
   a.direcccion= &lista_tokens[i].first;	//cout<<"muere aqui fuera3 "<<&lista_tokens[i].first<<endl;
   a.lexema=lista_tokens[i].second.first;
  /* if(lista_tokens[i+1].first=="OP_Asignacion_Igual" and( lista_tokens[i+2].first=="Num_Entero" or lista_tokens[i+2].first== "Num_Flotante"
  				or lista_tokens[i+2].first=="Cadena" or lista_tokens[i+2].first=="ID" ) )
   {
   		a.tipo=lista_tokens[i+2].first;  //token_igual = tipo
   		a.lexema_igual=lista_tokens[i+2].second.second;
   		cout<<"muere aqui if"<<endl;
   }*/
	
   
   //cout<<"ici"<<endl;
   if(lista_tokens[i].first=="ID")
   	tabla_de_simbolos.insert(std::pair<string, campos>(lista_tokens[i].second.first,a));
   //cout <<lista_tokens[i].second.first<<endl;
  }

}
///GRAMATICA Y REGLAS CORREGIDA			GRAM OK
//	TABLA DE SIMBOLOS LISTA|			TS COMPLETA
//	NO TERMINALES COMO ESTRUCTURA		ESTRUCTURA DE NO TERMINALES
	atributos PC_clave_Include_a;		
	atributos PROGRAMA_a;				
	atributos PC_clave_main_a;			
	atributos Parentesis_Abierto_a;		
	atributos Parentesis_Cerrado_a;		
	atributos Llave_Abierta_a;			
	atributos lista_sentencias_a;		
	atributos PC_Clave_return_a;		
	atributos Num_Entero_a;				
	atributos Punto_Coma_a;				
	atributos Llave_Cerrada_a;			
	atributos sentencia_a;				
	atributos e_a;						
	atributos tipo_dato_a;				
	atributos lista_def_a;				
	atributos def_basica_a;				
	atributos PC_Decl_int_a;			
	atributos PC_Decl_float_a;			
	atributos PC_Decl_double_a;			
	atributos PC_Decl_bool_a;			
	atributos PC_Decl_char_a;			
	atributos def_espec_a;				
	atributos lista_def1_a;				
	atributos Coma_a;					
	atributos ID_a;						
	atributos def_espec1_a; 			
	atributos acceso_array_a; 			
	atributos def_espec2_a; 			
	atributos simple_asign_a; 			
	atributos Corchete_Abierto_a; 		
	atributos Corchete_Cerrado_a; 		
	atributos OP_Asignacion_Igual_a; 	
	atributos sentencia1_a; 			
	atributos IF_ELSE_a;				
	atributos WHILE_a;					
	atributos Num_Flotante_a;			
	atributos F_a;						
	atributos F1_a;						
	atributos T_a;						
	atributos T1_a;						
	atributos E_a; 						
	atributos E1_a;						
	atributos W_a; 						
	atributos W1_a;						
	atributos operadores_a;				
	atributos PC_Clave_while_a;			
	atributos condicion_a;				
	atributos IF_a;						
	atributos IF_ELSE1_a;				
	atributos PC_Clave_if_a;			
	atributos PC_Clave_else_a;			
	atributos condicion_logica_a;		
	atributos condicion1_a;				
	atributos OP_Logico_And_a;			
	atributos OP_Logico_Or_a;			
	atributos operadores_log_a;			
	atributos OP_Relacional_Menor_a;		
	atributos OP_Relacional_Menor_Igual_a;	
	atributos OP_Relacional_Mayor_a;		
	atributos OP_Relacional_Mayor_Igual_a;	
	atributos OP_Relacional_Igual_a;		
	atributos OP_Relacional_Diferente_a; 	
	atributos op_aditivos_a;				
	atributos op_multiplicativos_a;			
	atributos OP_Aritmetico_Suma_a;			
	atributos OP_Aritmetico_Resta_a;		
	atributos OP_Aritmetico_Mult_a;			
	atributos OP_Aritmetico_Div_a;			
	atributos OP_Aritmetico_Mod_a;			
	terminales PROGRAMA;	
	terminales lista_sentencias;
	terminales def_basica;
	terminales tipo_dato;
	terminales lista_def;
	terminales lista_def1;
	terminales def_espec;
	terminales def_espec1;
	terminales def_espec2;
	terminales acceso_array;
	terminales simple_asign;
	terminales sentencia;
	terminales sentencia1;
	terminales WHILE;
	terminales IF_ELSE;
	terminales IF_ELSE1;
	terminales IF;
	terminales W1;
	terminales condicion;
	terminales condicion1;
	terminales condicion_logica;
	terminales operadores_log;
	terminales operadores;
	terminales op_aditivos;
	terminales op_multiplicativos;
	terminales E;
	terminales E1;
	terminales T;
	terminales T1;
	terminales F;
	terminales F1;

void inicializa_tabla_sintactica()
{
	vector< atributos > aux;

	//terminales PROGRAMA;
		aux.push_back(PC_clave_Include_a);
		aux.push_back(PROGRAMA_a);
		atributos f1;		f1.token="@f1";		aux.push_back(f1);
		PROGRAMA.PC_clave_Include=aux;
		aux.clear();

		aux.push_back(PC_Decl_int_a);
		aux.push_back(PC_clave_main_a);		
		aux.push_back(Parentesis_Abierto_a);
		aux.push_back(Parentesis_Cerrado_a);
		aux.push_back(Llave_Abierta_a);		
		aux.push_back(lista_sentencias_a);
		aux.push_back(PC_Clave_return_a);
		aux.push_back(Num_Entero_a);  
		aux.push_back(Punto_Coma_a);
		aux.push_back(Llave_Cerrada_a);
		PROGRAMA.PC_Decl_int=aux;
		aux.clear();
	//tabla_sintactica.insert(pair<string, pair<atributos, terminales> >(PROGRAMA2.token,(PROGRAMA2,PROGRAMA));
	tabla_sintactica.insert(make_pair(PROGRAMA_a.token,make_pair(PROGRAMA_a,PROGRAMA)));

//	terminales lista_sentencias;
		aux.push_back(sentencia_a);
		atributos f2;		f2.token="@f2";		aux.push_back(f2);
		aux.push_back(lista_sentencias_a);
		lista_sentencias.PC_Decl_int=aux;
		lista_sentencias.PC_Decl_float=aux;
		lista_sentencias.PC_Decl_double=aux;
		lista_sentencias.PC_Decl_bool=aux;
		lista_sentencias.PC_Decl_char=aux;
		lista_sentencias.Parentesis_Abierto=aux;
		lista_sentencias.Llave_Abierta=aux;
		lista_sentencias.ID=aux;
		lista_sentencias.PC_Clave_if=aux;
		lista_sentencias.PC_Clave_while=aux;
		lista_sentencias.Num_Entero=aux;////cualquier numero
		lista_sentencias.Num_Flotante=aux;
		aux.clear();

		aux.push_back(e_a);
		lista_sentencias.Llave_Cerrada=aux;
		lista_sentencias.PC_Clave_return=aux;
		aux.clear();
	//tabla_sintactica.insert(std::pair<string, terminales>("lista_sentencias",lista_sentencias));
	tabla_sintactica.insert(make_pair(lista_sentencias_a.token,make_pair(lista_sentencias_a,lista_sentencias)));

//	terminales def_basica;
		aux.push_back(tipo_dato_a);
		atributos f8a;		f8a.token="@f8a";		aux.push_back(f8a);
		aux.push_back(lista_def_a);
		atributos f8b;		f8b.token="@f8b";		aux.push_back(f8b);
		aux.push_back(Punto_Coma_a);
		def_basica.PC_Decl_int=aux;
		def_basica.PC_Decl_float=aux;
		def_basica.PC_Decl_double=aux;
		def_basica.PC_Decl_bool=aux;
		def_basica.PC_Decl_char=aux;
		aux.clear();
	
	tabla_sintactica.insert(make_pair(def_basica_a.token,make_pair(def_basica_a,def_basica)));

//	terminales tipo_dato;
		aux.push_back(PC_Decl_int_a);
		atributos f9a;		f9a.token="@f9a";		aux.push_back(f9a);
		tipo_dato.PC_Decl_int=aux;
		aux.clear();
		aux.push_back(PC_Decl_float_a);
		atributos f9b;		f9b.token="@f9b";		aux.push_back(f9b);
		tipo_dato.PC_Decl_float=aux;
		aux.clear();
		aux.push_back(PC_Decl_double_a);
		atributos f9c;		f9c.token="@f9c";		aux.push_back(f9c);
		tipo_dato.PC_Decl_double=aux;
		aux.clear();
		aux.push_back(PC_Decl_bool_a);
		atributos f9d;		f9d.token="@f9d";		aux.push_back(f9d);
		tipo_dato.PC_Decl_bool=aux;
		aux.clear();
		aux.push_back(PC_Decl_char_a);
		atributos f9e;		f9e.token="@f9e";		aux.push_back(f9e);
		tipo_dato.PC_Decl_char=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(tipo_dato_a.token,make_pair(tipo_dato_a,tipo_dato)));

//	terminales lista_def;

		atributos f10a;		f10a.token="@f10a";		aux.push_back(f10a);
		aux.push_back(def_espec_a);
		atributos f10b;		f10b.token="@f10b";		aux.push_back(f10b);
		aux.push_back(lista_def1_a);
		atributos f10c;		f10c.token="@f10c";		aux.push_back(f10c);
		lista_def.ID=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(lista_def_a.token,make_pair(lista_def_a,lista_def)));

//	terminales lista_def1;
		aux.push_back(e_a);
		lista_def1.Punto_Coma=aux;
		aux.clear();

		aux.push_back(Coma_a);
		atributos f11;		f11.token="@f11";		aux.push_back(f11);
		aux.push_back(lista_def_a);
		lista_def1.Coma=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(lista_def1_a.token, make_pair(lista_def1_a,lista_def1)));

//	terminales def_espec;
		aux.push_back(ID_a);
		atributos f12a;		f12a.token="@f12a";		aux.push_back(f12a);
		aux.push_back(def_espec1_a);
		atributos f12b;		f12b.token="@f12b";		aux.push_back(f12b);
		def_espec.ID=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(def_espec_a.token,make_pair(def_espec_a,def_espec)));

//	terminales def_espec1;
		aux.push_back(acceso_array_a);
		aux.push_back(def_espec2_a);		
		atributos f13b;		f13b.token="@f13b";		aux.push_back(f13b);
		def_espec1.Corchete_Abierto=aux;
		aux.clear();

		aux.push_back(e_a);
		def_espec1.Punto_Coma=aux;
		def_espec1.Coma=aux;
		aux.clear();

		aux.push_back(simple_asign_a);
		atributos f13a;		f13a.token="@f13a";		aux.push_back(f13a);
		def_espec1.OP_Asignacion_Igual=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(def_espec1_a.token,make_pair(def_espec1_a,def_espec1)));

//	terminales def_espec2;
		aux.push_back(e_a);
		def_espec2.Punto_Coma=aux;
		def_espec2.Coma=aux;
		aux.clear();

		aux.push_back(simple_asign_a);
		atributos f14;		f14.token="@f14";		aux.push_back(f14);
		def_espec2.OP_Asignacion_Igual=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(def_espec2_a.token, make_pair(def_espec2_a,def_espec2)));

//	terminales acceso_array;
		aux.push_back(Corchete_Abierto_a);
		aux.push_back(Num_Entero_a);
		aux.push_back(Corchete_Cerrado_a);
		acceso_array.Corchete_Abierto=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(acceso_array_a.token, make_pair(acceso_array_a,acceso_array)));
	
//	terminales simple_asign;
		aux.push_back(e_a);
		simple_asign.Punto_Coma=aux;
		simple_asign.Coma=aux;
		aux.clear();

		aux.push_back(OP_Asignacion_Igual_a);
		aux.push_back(E_a);
		atributos f15;		f15.token="@f15";		aux.push_back(f15);
		simple_asign.OP_Asignacion_Igual=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(simple_asign_a.token, make_pair(simple_asign_a,simple_asign)));

//	terminales sentencia;
		aux.push_back(Parentesis_Abierto_a);
		aux.push_back(E_a);
		aux.push_back(Parentesis_Cerrado_a);
		aux.push_back(Punto_Coma_a);
		sentencia.Parentesis_Abierto=aux;
		aux.clear();

		aux.push_back(ID_a);
		atributos f3a;		f3a.token="@f3a";		aux.push_back(f3a);
		aux.push_back(sentencia1_a);
		aux.push_back(Punto_Coma_a);
		atributos f3b;		f3b.token="@f3b";		aux.push_back(f3b);
		sentencia.ID=aux;
		aux.clear();

		aux.push_back(IF_ELSE_a);
		sentencia.PC_Clave_if=aux;
		aux.clear();

		aux.push_back(WHILE_a);
		atributos f3d;		f3d.token="@f3d";		aux.push_back(f3d);
		sentencia.PC_Clave_while=aux;
		aux.clear();

		aux.push_back(Num_Entero_a);
		aux.push_back(T1_a);
		aux.push_back(E1_a);
		aux.push_back(Punto_Coma_a);
		sentencia.Num_Entero=aux;
		aux.clear();

		aux.push_back(Num_Flotante_a);
		aux.push_back(T1_a);
		aux.push_back(E1_a);
		aux.push_back(Punto_Coma_a);
		sentencia.Num_Flotante=aux;
		aux.clear();
		/////AQUI
		aux.push_back(def_basica_a);
		atributos f3c;		f3c.token="@f3c";		aux.push_back(f3c);
		sentencia.PC_Decl_int=aux;
		sentencia.PC_Decl_float=aux;
		sentencia.PC_Decl_double=aux;
		sentencia.PC_Decl_bool=aux;
		sentencia.PC_Decl_char=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(sentencia_a.token,make_pair(sentencia_a,sentencia)));

//	terminales sentencia1;
		aux.push_back(F1_a);
		aux.push_back(T1_a);
		aux.push_back(E1_a);
		aux.push_back(Punto_Coma_a);
		sentencia1.Corchete_Abierto=aux;
		aux.clear();

		aux.push_back(e_a);
		sentencia1.Punto_Coma=aux;
		aux.clear();

		aux.push_back(def_espec1_a);
		atributos f4;		f4.token="@f4";		aux.push_back(f4);
		sentencia1.OP_Asignacion_Igual=aux;
		aux.clear();

		aux.push_back(operadores_a);
		aux.push_back(OP_Asignacion_Igual_a);
		aux.push_back(E_a);
		sentencia1.OP_Aritmetico_Suma=aux;
		sentencia1.OP_Aritmetico_Resta=aux;
		sentencia1.OP_Aritmetico_Mult=aux;
		sentencia1.OP_Aritmetico_Div=aux;
		sentencia1.OP_Aritmetico_Mod=aux;
		aux.clear();

		aux.push_back(def_espec1_a);
		sentencia1.ID=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(sentencia1_a.token, make_pair(sentencia1_a,sentencia1)));

//	terminales WHILE;
		aux.push_back(PC_Clave_while_a);
		atributos f5a;		f5a.token="@f5a";		aux.push_back(f5a);
		aux.push_back(Parentesis_Abierto_a);
		aux.push_back(condicion_a);
		aux.push_back(Parentesis_Cerrado_a);
		aux.push_back(W1_a);
		atributos f5b;		f5b.token="@f5b";		aux.push_back(f5b);
		WHILE.PC_Clave_while=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(WHILE_a.token, make_pair(WHILE_a,WHILE)));

//	terminales IF_ELSE;
		aux.push_back(IF_a);
		atributos f6a;		f6a.token="@f6a";		aux.push_back(f6a);
		aux.push_back(IF_ELSE1_a);
		atributos f6b;		f6b.token="@f6b";		aux.push_back(f6b);
		IF_ELSE.PC_Clave_if=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(IF_ELSE_a.token, make_pair(IF_ELSE_a,IF_ELSE)));

//	terminales IF_ELSE1;
		aux.push_back(PC_Clave_else_a);
		aux.push_back(W1_a);
		atributos f7;		f7.token="@f7";		aux.push_back(f7);
		IF_ELSE1.PC_Clave_else=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(IF_ELSE1_a.token,make_pair(IF_ELSE1_a,IF_ELSE1)));

//	terminales IF;
		atributos f16a;		f16a.token="@f16a";		aux.push_back(f16a);
		aux.push_back(PC_Clave_if_a);
		aux.push_back(Parentesis_Abierto_a);
		aux.push_back(condicion_a);
		aux.push_back(Parentesis_Cerrado_a);
		aux.push_back(W1_a);
		atributos f16b;		f16b.token="@f16b";		aux.push_back(f16b);
		IF.PC_Clave_if=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(IF_a.token,make_pair(IF_a,IF)));

//	terminales W1;
		aux.push_back(sentencia_a);
		atributos f17a;		f17a.token="@f17a";		aux.push_back(f17a);
		W1.PC_Decl_int=aux;
		W1.PC_Decl_float=aux;
		W1.PC_Decl_double=aux;
		W1.PC_Decl_bool=aux;
		W1.PC_Decl_char=aux;
		W1.Parentesis_Abierto=aux;
		W1.ID=aux;
		aux.clear();

		aux.push_back(Llave_Abierta_a);
		aux.push_back(lista_sentencias_a);
		aux.push_back(Llave_Cerrada_a);
		atributos f17b;		f17b.token="@f17b";		aux.push_back(f17b);
		W1.Llave_Abierta=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(W1_a.token,make_pair(W1_a,W1)));
	
//	terminales condicion;
		aux.push_back(condicion_logica_a);
		atributos f18;		f18.token="@f18";		aux.push_back(f18);
		aux.push_back(condicion1_a);
		condicion.Llave_Abierta=aux;
		condicion.ID=aux;
		condicion.Num_Entero=aux;
		condicion.Num_Flotante=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(condicion_a.token, make_pair(condicion_a,condicion)));
	
//	terminales condicion1;
		aux.push_back(e_a);
		condicion1.Parentesis_Cerrado=aux;
		aux.clear();

		aux.push_back(OP_Logico_And_a);
		aux.push_back(condicion_logica_a);
		condicion1.OP_Logico_And=aux;
		aux.clear();

		aux.push_back(OP_Logico_Or_a);
		aux.push_back(condicion_logica_a);
		condicion1.OP_Logico_Or=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(condicion1_a.token, make_pair(condicion1_a,condicion1)));

//	terminales condicion_logica;
		aux.push_back(E_a);
		aux.push_back(operadores_log_a);
		aux.push_back(E_a);
		atributos f20;		f20.token="@f20";		aux.push_back(f20);
		condicion_logica.Parentesis_Abierto=aux;
		condicion_logica.ID=aux;
		condicion_logica.Num_Entero=aux;
		condicion_logica.Num_Flotante=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(condicion_logica_a.token, make_pair(condicion_logica_a,condicion_logica)));

//	terminales operadores_log;
		aux.push_back(OP_Relacional_Menor_a);
		atributos f21b;		f21b.token="@f21b";		aux.push_back(f21b);
		operadores_log.OP_Relacional_Menor=aux;
		aux.clear();

		aux.push_back(OP_Relacional_Mayor_a);
		atributos f21a;		f21a.token="@f21a";		aux.push_back(f21a);		
		operadores_log.OP_Relacional_Mayor=aux;
		aux.clear();

		aux.push_back(OP_Relacional_Mayor_Igual_a);
		atributos f21c;		f21c.token="@f21c";		aux.push_back(f21c);
		operadores_log.OP_Relacional_Mayor_Igual=aux;
		aux.clear();

		aux.push_back(OP_Relacional_Menor_Igual_a);
		atributos f21d;		f21d.token="@f21d";		aux.push_back(f21d);
		operadores_log.OP_Relacional_Menor_Igual=aux;
		aux.clear();

		aux.push_back(OP_Relacional_Igual_a);
		atributos f21e;		f21e.token="@f21e";		aux.push_back(f21e);
		operadores_log.OP_Relacional_Igual=aux;
		aux.clear();

		aux.push_back(OP_Relacional_Diferente_a);		
		atributos f21f;		f21f.token="@f21f";		aux.push_back(f21f);
		operadores_log.OP_Relacional_Diferente=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(operadores_log_a.token,make_pair(operadores_log_a,operadores_log)));

//	terminales operadores;
		aux.push_back(op_aditivos_a);
		atributos f22a;		f22a.token="@f22a";		aux.push_back(f22a);
		operadores.OP_Aritmetico_Suma=aux;
		operadores.OP_Aritmetico_Resta=aux;
		aux.clear();

		aux.push_back(op_multiplicativos_a);
		atributos f22b;		f22b.token="@f22b";		aux.push_back(f22b);
		operadores.OP_Aritmetico_Mult=aux;
		operadores.OP_Aritmetico_Div=aux;
		operadores.OP_Aritmetico_Mod=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(operadores_a.token,make_pair(operadores_a,operadores)));
	
//	terminales op_aditivos;
		aux.push_back(OP_Aritmetico_Suma_a);
		atributos f23a;		f23a.token="@f23a";		aux.push_back(f23a);
		op_aditivos.OP_Aritmetico_Suma=aux;
		aux.clear();

		aux.push_back(OP_Aritmetico_Resta_a);
		atributos f23b;		f23b.token="@f23b";		aux.push_back(f23b);
		op_aditivos.OP_Aritmetico_Resta=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(op_aditivos_a.token,make_pair(op_aditivos_a,op_aditivos)));

//	terminales op_multiplicativos;
		aux.push_back(OP_Aritmetico_Mult_a);
		atributos f24a;		f24a.token="@f24a";		aux.push_back(f24a);
		op_multiplicativos.OP_Aritmetico_Mult=aux;
		aux.clear();

		aux.push_back(OP_Aritmetico_Div_a);
		atributos f24b;		f24b.token="@f24b";		aux.push_back(f24b);
		op_multiplicativos.OP_Aritmetico_Div=aux;
		aux.clear();

		aux.push_back(OP_Aritmetico_Mod_a);
		atributos f24c;		f24c.token="@f24c";		aux.push_back(f24c);
		op_multiplicativos.OP_Aritmetico_Mod=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(op_multiplicativos_a.token,make_pair(op_multiplicativos_a,op_multiplicativos)));

//	terminales E;
		aux.push_back(Parentesis_Abierto_a);
		aux.push_back(E_a);
		aux.push_back(Parentesis_Cerrado_a);
		atributos f25c;		f25c.token="@f25c";		aux.push_back(f25c);
		E.Parentesis_Abierto=aux;
		aux.clear();

		aux.push_back(T_a);
		atributos f25a;		f25a.token="@f25a";		aux.push_back(f25a);
		aux.push_back(E1_a);
		atributos f25b;		f25b.token="@f25b";		aux.push_back(f25b);
		E.ID=aux;
		E.Num_Entero=aux;
		E.Num_Flotante=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(E_a.token,make_pair(E_a,E)));
	//////FALTA 
//	terminales E1;
		aux.push_back(e_a);
		E1.Parentesis_Cerrado=aux;
		E1.Punto_Coma=aux;
		E1.Coma=aux;
		E1.OP_Logico_And=aux;
		E1.OP_Logico_Or=aux;
		E1.OP_Relacional_Menor=aux;
		E1.OP_Relacional_Mayor=aux;
		E1.OP_Relacional_Mayor_Igual=aux;
		E1.OP_Relacional_Menor_Igual=aux;
		E1.OP_Relacional_Igual=aux;
		E1.OP_Relacional_Diferente=aux;
		aux.clear();

		aux.push_back(op_aditivos_a);
		aux.push_back(E_a);
		atributos f26;		f26.token="@f26";		aux.push_back(f26);
		E1.OP_Aritmetico_Suma=aux;
		E1.OP_Aritmetico_Resta=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(E1_a.token,make_pair(E1_a,E1)));
//	terminales T;
		aux.push_back(F_a);
		aux.push_back(T1_a);
		T.ID=aux;
		T.Num_Entero=aux;
		T.Num_Flotante=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(T_a.token,make_pair(T_a,T)));
//	terminales T1;
		aux.push_back(e_a);
		T1.Parentesis_Cerrado=aux;
		T1.Punto_Coma=aux;
		T1.Coma=aux;
		T1.OP_Logico_And=aux;
		T1.OP_Logico_Or=aux;
		T1.OP_Relacional_Menor=aux;
		T1.OP_Relacional_Mayor=aux;
		T1.OP_Relacional_Mayor_Igual=aux;
		T1.OP_Relacional_Menor_Igual=aux;
		T1.OP_Relacional_Igual=aux;
		T1.OP_Relacional_Diferente=aux;
		T1.OP_Aritmetico_Suma=aux;
		T1.OP_Aritmetico_Resta=aux;
		aux.clear();

		aux.push_back(op_multiplicativos_a);
		aux.push_back(T_a);
		atributos f28;		f28.token="@f28";		aux.push_back(f28);
		T1.OP_Aritmetico_Mult=aux;
		T1.OP_Aritmetico_Div=aux;
		T1.OP_Aritmetico_Mod=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(T1_a.token, make_pair(T1_a,T1)));
//	terminales F;
		aux.push_back(ID_a);
		aux.push_back(F1_a);
		F.ID=aux;
		aux.clear();
		
		aux.push_back(Num_Flotante_a);
		atributos f29c;		f29c.token="@f29c";		aux.push_back(f29c);
		F.Num_Flotante=aux;
		aux.clear();

		aux.push_back(Num_Entero_a);
		atributos f29b;		f29b.token="@f29b";		aux.push_back(f29b);
		F.Num_Entero=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(F_a.token,make_pair(F_a,F)));
//	terminales F1;
		aux.push_back(e_a);
		F1.Parentesis_Cerrado=aux;
		F1.Punto_Coma=aux;
		F1.Coma=aux;
		F1.OP_Logico_And=aux;
		F1.OP_Logico_Or=aux;
		F1.OP_Relacional_Menor=aux;
		F1.OP_Relacional_Mayor=aux;
		F1.OP_Relacional_Mayor_Igual=aux;
		F1.OP_Relacional_Menor_Igual=aux;
		F1.OP_Relacional_Igual=aux;
		F1.OP_Relacional_Diferente=aux;
		F1.OP_Aritmetico_Suma=aux;
		F1.OP_Aritmetico_Resta=aux;
		F1.OP_Aritmetico_Mult=aux;
		F1.OP_Aritmetico_Div=aux;
		F1.OP_Aritmetico_Mod=aux;	
		aux.clear();

		aux.push_back(acceso_array_a);
		F1.Corchete_Abierto=aux;
		aux.clear();
	tabla_sintactica.insert(make_pair(F1_a.token,make_pair(F1_a,F1)));
}
string getType(string llave)
{
	return tabla_de_simbolos[llave].tipo;
}
void setType(string llave, string tipo)
{
	//map<string,campos>::iterator it;
	//cout<<"This is the key; "<<llave<<endl;
	tabla_de_simbolos[llave].tipo=tipo;
	if(tipo=="int") tabla_de_simbolos[llave].tamanho=4;
	else if(tipo=="float") tabla_de_simbolos[llave].tamanho=8;
	else if(tipo=="double") tabla_de_simbolos[llave].tamanho=16;
	else if(tipo=="bool") tabla_de_simbolos[llave].tamanho=1;
	else if(tipo=="char") tabla_de_simbolos[llave].tamanho=4;
}
void setAddress(string llave, int desp)
{
	tabla_de_simbolos[llave].dir=desp;
}
void setValue(string llave, string val)
{
	tabla_de_simbolos[llave].valor=val;
}
void setValueArr(string llave, int posicion, string val)
{

}
int getSize(string llave) 
{
	return tabla_de_simbolos[llave].tamanho;
}
int desplazamiento=0;
ofstream ficheroSalida;

bool f1()
{
	desplazamiento=0;
	return true;
}
bool f2()
{
	lista_sentencias_a.codigo=sentencia_a.codigo;
	cout<<"CODIGO: "<<lista_sentencias_a.codigo<<endl;
//	ficheroSalida.open ("CodigoIntermedio.txt");
	ficheroSalida <<lista_sentencias_a.codigo;
//	ficheroSalida.close();
	return true;
}
bool f3a()
{
	if(getType(ID_a.lexema).size()!=0)
	{
		sentencia1_a.type=ID_a.type;
		sentencia1_a.lexema=ID_a.lexema;
		sentencia1_a.value=ID_a.value;
	}	
	else
	{
		cout<<"Error de definicion"<<endl;
		lista_errores_semanticos.push_back(make_pair("Error de definicion",make_pair(ID_a.lexema,linea_actual)));
		return false;
	}
	return true;
}
bool f3b()
{
	sentencia_a.codigo=sentencia1_a.codigo;
	cout<<"CODIGO"<<sentencia_a.codigo<<endl;
	return true;
}
bool f3c()
{
	sentencia_a.codigo=def_basica_a.codigo;
	cout<<"CODIGO"<<sentencia_a.codigo<<endl;
	return true;
}
bool f3d()
{
	sentencia_a.codigo=WHILE_a.codigo;
	cout<<"CODIGO"<<sentencia_a.codigo<<endl;
	return true;
}
bool f4()
{
	sentencia1_a.codigo=def_espec1_a.codigo;
	cout<<"CODIGO"<<sentencia_a.codigo<<endl;
	return true;
}
int identif=1;
bool f5a()
{
	WHILE_a.comienzo="Etiqueta comienzo while"+to_string(identif);
	WHILE_a.despues="Etiqueta despues while"+to_string(identif);
	identif++;
	return true;
}
bool f5b()
{
	WHILE_a.codigo=WHILE_a.comienzo+":\n"+
					"\t"+condicion_a.codigo+"\n"+
					"\t"+"if "+condicion_a.lugar+" = 0 goto "+WHILE_a.despues+"\n"+
					"\t"+W1_a.codigo+"\n"+
					"\t"+"goto "+WHILE_a.comienzo+"\n"+
					WHILE_a.despues+":"+"\n";
	cout<<"HERE: "<<WHILE_a.codigo<<endl;
	return true;
}
bool f6a()
{
	IF_ELSE1_a.codigo=IF_a.codigo;
	IF_ELSE1_a.comienzo=IF_a.despues;
	cout<<"CODIGO"<<IF_ELSE1_a.codigo<<endl;
	return true;
}
bool f6b()
{
	IF_ELSE_a.codigo=IF_ELSE1_a.codigo;
	cout<<"CODIGO"<<IF_ELSE1_a.codigo<<endl;
	return true;
}
bool f7()
{
	IF_ELSE1_a.despues="Etiqueta nueva"+to_string(identif);
	IF_ELSE1_a.codigo+="goto "+IF_ELSE1_a.despues+"\n"+
						"\t"+IF_ELSE1_a.comienzo+" : "+"\n"+
						"\t \t"+W1_a.codigo+"\n"+
						"\t"+IF_ELSE1_a.despues+" : "+"\n";
	cout<<"CODIGO"<<IF_ELSE1_a.codigo<<endl;
	return true;
}
////DECLARACIONES
bool f8a()
{
	lista_def_a.type=tipo_dato_a.type;
	return true;
}
bool f8b()
{
	def_basica_a.codigo = lista_def_a.codigo;
	cout<<"CODIGO: "<<def_basica_a.codigo<<endl;
	return true;
}
bool f9a()
{
	tipo_dato_a.type="int";
	tipo_dato_a.dir=desplazamiento;
	//tipo_dato_a.tamanho=4;
	desplazamiento+=4;
	return true;
}
bool f9b()
{
	tipo_dato_a.type="float";
	tipo_dato_a.dir=desplazamiento;
	//tipo_dato_a.tamanho=8;
	desplazamiento+=8;
	return true;
}
bool f9c()
{
	tipo_dato_a.type="double";
	tipo_dato_a.dir=desplazamiento;
	//tipo_dato_a.tamanho=16;
	desplazamiento+=16;
	return true;
}
bool f9d()
{
	tipo_dato_a.type="bool";
	tipo_dato_a.dir=desplazamiento;
	//tipo_dato_a.tamanho=1;
	desplazamiento+=1;
	return true;
}
bool f9e()
{
	tipo_dato_a.type="char";
	tipo_dato_a.dir=desplazamiento;
	//tipo_dato_a.tamanho=4;
	desplazamiento+=4;
	return true;
}
bool f10a()
{
	def_espec_a.type=lista_def_a.type;
	return true;
}
bool f10b()
{
	lista_def1_a.type=def_espec_a.type;
	lista_def1_a.codigo=def_espec_a.codigo;
	cout<<"CODIGO: "<<lista_def1_a.codigo<<endl;
	return true;
}
bool f10c()
{
	lista_def_a.codigo=lista_def1_a.codigo;
	cout<<"CODIGO: "<<lista_def_a.codigo<<endl;
	return true;
}
bool f11()
{
	lista_def_a.type=lista_def1_a.type;
	return true;
}
bool f12a()
{
	//cout<<"ESTOY AQUI 0 : "<<ID_a.lexema<<endl;
	setType(ID_a.lexema,def_espec_a.type);
	//cout<<"ESTOY AQUI 0 : "<<ID_a.type<<endl;
	def_espec1_a.lexema=ID_a.lexema;
	setAddress(ID_a.lexema,desplazamiento);
	return true;
}
bool f12b()
{
	def_espec_a.codigo=def_espec1_a.codigo;
	cout<<"CODIGO: "<<def_espec_a.codigo<<endl;
	return true;
}
bool f13a()
{
	//cout<<"COMPRARCION: "<<getType(def_espec1_a.lexema)<<" == "<<simple_asign_a.type<<endl;
	if(getType(def_espec1_a.lexema)== simple_asign_a.type)
	{
		//cout<<"ICI: "<<simple_asign_a.value<<endl;
		setValue(def_espec1_a.lexema,simple_asign_a.value);
	}
	else
	{
		cout<<"ERROR: Los tipos no coinciden"<<endl;
		return false;
	}
	return true;
}
bool f13b()
{
	if(getType(def_espec1_a.lexema)== def_espec2_a.type)
	{
		if(acceso_array_a.pos<getSize(def_espec1_a.lexema))

			setValueArr(def_espec1_a.lexema,acceso_array_a.pos,def_espec2_a.value);
		else
		{
			cout<<"ERROR:Indice fuera de limite"<<endl;
			return false;
		}
	}
	else
	{
		cout<<"ERROR: Los tipos no coinciden"<<endl;
		return false;
	}
	return true;
}
bool f14()
{
	def_espec2_a.type=simple_asign_a.type;
	def_espec2_a.value=simple_asign_a.value;
	return true;
}
bool f15()
{
	simple_asign_a.type="int";//E_a.type;
	simple_asign_a.value=E_a.value;
	simple_asign_a.codigo=" ";//E_a.codigo;	
	cout<<"CODIGO: "<<simple_asign_a.codigo<<endl;
	return true;
}
////HASTA AQUI DECLARACIONEs
bool f16a()
{
	IF_a.despues="Etiqueta nueva "+to_string(identif);
	return true;
}
bool f16b()
{
	IF_a.codigo=condicion_a.codigo+"\n"+
				"if"+condicion_a.lugar+" = 0 goto "+IF_a.despues+"\n"+
				"\t"+W1_a.codigo+"\n"+
				IF_a.despues+" : \n";

	cout<<"CODIGO: "<<IF_a.codigo<<endl;
	return false;
}
bool f17a()
{
	W1_a.codigo=sentencia_a.codigo;
	cout<<"CODIGO: "<<W1_a.codigo<<endl;
	return true;
}
bool f17b()
{
	W1_a.codigo=lista_sentencias_a.codigo;
	cout<<"CODIGO: "<<W1_a.codigo<<endl;
	return true;
}
bool f18()
{
	condicion_a.codigo=condicion_logica_a.codigo;
	condicion_a.lugar=condicion_logica_a.lugar;
	cout<<"CODIGO: "<<condicion_a.codigo<<endl;
	return true;
}
bool f20()
{
	condicion_logica_a.lugar="temp_nuevo";
	condicion_logica_a.codigo=E_a.codigo+"\n"+E_a.codigo+"\n"+
							"\t"+condicion_logica_a.lugar+" = "+E_a.lugar+operadores_log_a.lexema+E_a.lugar+"\n";

	cout<<"CODIGO: "<<condicion_logica_a.codigo<<endl;
	return true;
}
bool f21a()
{
	operadores_log_a.lexema=">";
	return true;
}
bool f21b()
{
	operadores_log_a.lexema="<";
	return true;
}
bool f21c()
{
	operadores_log_a.lexema=">=";
	return true;
}
bool f21d()
{
	operadores_log_a.lexema="<=";
	return true;
}
bool f21e()
{
	operadores_log_a.lexema="==";
	return true;
}
bool f21f()
{
	operadores_log_a.lexema="!=";
	return true;
}
bool f22a()
{
	operadores_a.lexema=op_aditivos_a.lexema;
	return true;
}
bool f22b()
{
	operadores_a.lexema=op_multiplicativos_a.lexema;
	return true;
}
bool f23a()
{
	op_aditivos_a.lexema="+";
	return true;
}
bool f23b()
{
	op_aditivos_a.lexema="-";
	return true;
}
bool f24a()
{
	op_multiplicativos_a.lexema="*";
	return true;
}
bool f24b()
{
	op_multiplicativos_a.lexema="/";
	return true;
}
bool f24c()
{
	op_multiplicativos_a.lexema="%";
	return true;
}
bool f25a()
{
	E1_a.type=T_a.type;
	E1_a.value=T_a.value;
	E1_a.codigo=T_a.codigo;
	E1_a.lugar=T_a.lugar;
	cout<<"CODIGO: "<<E1_a.codigo<<endl;
	return true;
}
bool f25b()
{
	E_a.type=E1_a.type;
	E_a.value=E1_a.value;
	E_a.codigo=E1_a.codigo;
	E_a.lugar=E1_a.lugar;	
	cout<<"CODIGO: "<<E_a.codigo<<endl;
	return true;
}
bool f25c()
{
	E_a.type=E_a.type;
	E_a.value=E_a.value;
	E_a.codigo=E_a.codigo;
	E_a.lugar=E_a.lugar;
	cout<<"CODIGO: "<<E_a.codigo<<endl;
	return true;
}
bool f26()
{
	if(E1_a.type==E_a.type and E1_a.lexema.size()!=0)
	{
		if(op_aditivos_a.lexema=="+")
			E1_a.value=atoi(E1_a.value.c_str())+atoi(E_a.value.c_str());
		else if(op_aditivos_a.lexema=="-")
			E1_a.value=atoi(E1_a.value.c_str())-atoi(E_a.value.c_str());
		else 
			{			
			cout<<"Error operador invalido"<<endl;
			return false;
			}			
		E1_a.lugar="temp_nuevo";
		E1_a.codigo=E1_a.codigo+"\n"+
					E_a.codigo+"\n"+
					E1_a.lugar+" = "+T1_a.lugar+op_aditivos_a.lexema+E_a.lugar;

		cout<<"CODIGO: "<<E1_a.codigo<<endl;
	}
	else
		cout<<"Las variables no coinciden en tipo"<<endl;
}
bool f28()
{
	if(T1_a.type==T_a.type and T1_a.lexema.size()!=0)
	{
		if(op_multiplicativos_a.lexema=="*")
			T1_a.value=atoi(T1_a.value.c_str())*atoi(T_a.value.c_str());
		else if(op_multiplicativos_a.lexema=="/")
			T1_a.value=atoi(T1_a.value.c_str())/atoi(T_a.value.c_str());
		else if(op_multiplicativos_a.lexema=="%")
			T1_a.value=atoi(T1_a.value.c_str())%atoi(T_a.value.c_str());
		else 
			{			
			cout<<"Error operador invalido"<<endl;
			return false;
			}			
		T1_a.lugar="temp_nuevo";
		T1_a.codigo=T1_a.codigo+"\n"+
					T_a.codigo+"\n"+
					T1_a.lugar+" = "+T1_a.lugar+op_multiplicativos_a.lexema+T_a.lugar;

		cout<<"CODIGO: "<<T1_a.codigo<<endl;
	}
	else
		cout<<"Las variables no coinciden en tipo"<<endl;
}
bool f29a()
{

}
bool f29b()
{
	F_a.type="int";
	F_a.lugar=Num_Entero_a.lexema;
	F_a.value=Num_Entero_a.lexema;
	F_a.codigo=" ";
}
bool f29c()
{
	F_a.type="float";
	F_a.lugar=Num_Flotante_a.lexema;
	F_a.value=Num_Flotante_a.lexema;
	F_a.codigo=" ";
}
bool f30()
{

}
void inicializa_pila()
{
	atributos vacio; vacio.token="$";
	pila.push(vacio);
	atributos PROGRAMA1; PROGRAMA1.token="PROGRAMA";
	pila.push(PROGRAMA1);
}
bool es_terminal(string a)
{
	if(a=="PC_clave_main" 
|| a=="PC_clave_Include"
|| a=="PC_Decl_bool"
|| a=="PC_Decl_char"
|| a=="PC_Decl_float"
|| a=="PC_Decl_double"
|| a=="PC_Decl_int"
|| a=="PC_Decl_long"
|| a=="PC_Clave_else"
|| a=="PC_Clave_for"
|| a=="PC_Clave_if"
|| a=="PC_Clave_return"
|| a=="PC_Clave_while"
|| a=="OP_Aritmetico_Suma"
|| a=="OP_Aritmetico_Resta"
|| a=="OP_Aritmetico_Mult"
|| a=="OP_Aritmetico_Div"
|| a=="OP_Aritmetico_Mod"
|| a=="OP_Asignacion_Igual"
|| a=="OP_Asignacion_Mas_Igual"
|| a=="OP_Asignacion_Menos_Igual"
|| a=="OP_Asignacion_Por_Igual"
|| a=="OP_Asignacion_Entre_Igual"
|| a=="OP_Relacional_Igual"
|| a=="OP_Relacional_Menor"
|| a=="OP_Relacional_Mayor"
|| a=="OP_Relacional_Menor_Igual"
|| a=="OP_Relacional_Mayor_Igual"
|| a=="OP_Relacional_Diferente"
|| a=="OP_Logico_And"
|| a=="OP_Logico_Or"
|| a=="OP_Logico_Negacion"
|| a=="Llave_Abierta"
|| a=="Llave_Cerrada"
|| a=="Parentesis_Abierto"
|| a=="Parentesis_Cerrado"
|| a=="Corchete_Abierto"
|| a=="Corchete_Cerrado"
|| a=="Punto_Coma"
|| a=="Coma"
|| a=="OP_Mas_Mas"
|| a=="OP_Menos_Menos"
|| a=="Num_Entero"
|| a=="Num_Flotante"
|| a=="ID"
|| a=="cadena")
		return true;
    return false;
}
vector<atributos> busqueda_tabla(atributos a, string token_actual)
{
	terminales baux =tabla_sintactica[a.token].second;
	//if(token_actual=="PC_clave_main" )return baux.PC_clave_main;
	if(token_actual=="PC_clave_Include")return baux.PC_clave_Include;
	if(token_actual=="PC_Decl_bool")return baux.PC_Decl_bool;
	if(token_actual=="PC_Decl_char")return baux.PC_Decl_char;
	if(token_actual=="PC_Decl_float")return baux.PC_Decl_float;
	if(token_actual=="PC_Decl_double")return baux.PC_Decl_double;
	if(token_actual=="PC_Decl_int")return baux.PC_Decl_int;
	//if(token_actual=="PC_Decl_long")return baux.PC_Decl_long;
	if(token_actual=="PC_Clave_else")return baux.PC_Clave_else;
	//if(token_actual=="PC_Clave_for")return baux.PC_Clave_for;
	if(token_actual=="PC_Clave_return")return baux.PC_Clave_return;
	if(token_actual=="PC_Clave_while")return baux.PC_Clave_while;
	if(token_actual=="OP_Aritmetico_Suma")return baux.OP_Aritmetico_Suma;
	if(token_actual=="OP_Aritmetico_Resta")return baux.OP_Aritmetico_Resta;
	if(token_actual=="OP_Aritmetico_Mult")return baux.OP_Aritmetico_Mult;
	if(token_actual=="OP_Aritmetico_Div")return baux.OP_Aritmetico_Div;
	if(token_actual=="OP_Aritmetico_Mod")return baux.OP_Aritmetico_Mod;
	if(token_actual=="OP_Asignacion_Igual")return baux.OP_Asignacion_Igual;
	//if(token_actual=="OP_Asignacion_Mas_Igual")return baux.OP_Asignacion_Mas_Igual;
	//if(token_actual=="OP_Asignacion_Menos_Igual")return baux.OP_Asignacion_Menos_Igual;
	//if(token_actual=="OP_Asignacion_Por_Igual")return baux.OP_Asignacion_Por_Igual;
	//if(token_actual=="OP_Asignacion_Entre_Igual")return baux.OP_Asignacion_Entre_Igual;
	if(token_actual=="OP_Relacional_Igual")return baux.OP_Relacional_Igual;
	if(token_actual=="OP_Relacional_Menor")return baux.OP_Relacional_Menor;
	if(token_actual=="OP_Relacional_Mayor")return baux.OP_Relacional_Mayor;
	if(token_actual=="OP_Relacional_Menor_Igual")return baux.OP_Relacional_Menor_Igual;
	if(token_actual=="OP_Relacional_Mayor_Igual")return baux.OP_Relacional_Mayor_Igual;
	if(token_actual=="OP_Relacional_Diferente")return baux.OP_Relacional_Diferente;
	if(token_actual=="OP_Logico_And")return baux.OP_Logico_And;
	if(token_actual=="OP_Logico_Or")return baux.OP_Logico_Or;
	//if(token_actual=="OP_Logico_Negacion")return baux.OP_Logico_Negacion;
	if(token_actual=="Llave_Abierta")return baux.Llave_Abierta;
	if(token_actual=="Llave_Cerrada")return baux.Llave_Cerrada;
	if(token_actual=="Parentesis_Abierto")return baux.Parentesis_Abierto;
	if(token_actual=="Parentesis_Cerrado")return baux.Parentesis_Cerrado;
	if(token_actual=="Corchete_Abierto")return baux.Corchete_Abierto;
	if(token_actual=="Corchete_Cerrado")return baux.Corchete_Cerrado;
	if(token_actual=="Punto_Coma")return baux.Punto_Coma;
	if(token_actual=="Coma")return baux.Coma;
	//if(token_actual=="OP_Mas_Mas")return baux.OP_Mas_Mas;
	//if(token_actual=="OP_Menos_Menos")return baux.OP_Menos_Menos;
	if(token_actual=="Num_Entero")return baux.Num_Entero;
	if(token_actual=="Num_Flotante")return baux.Num_Flotante;
	if(token_actual=="ID")return baux.ID;
	//if(token_actual=="cadena")return baux.cadena;
	
}
bool analisis_sintactico()
{
	inicializa_tabla_sintactica();
	inicializa_pila();
	int i=0;
	while(i<lista_tokens.size() and !pila.empty() )
	{
		atributos a=pila.top();
		  for(int i=0; i<lista_tokens.size();i++)
  			if (lista_tokens[i].first==a.token or lista_tokens[i].second.first==a.lexema)
				{linea_actual=lista_tokens[i].second.second;
					break;
				}
		cout<<"..."<<a.token<<endl;//" , "<<a.lexema<<endl;
		if(a.token=="ε")
		{  
			//i++;
			pila.pop();
		}
		else if(a.token[0]=='@')
		{	string caso= a.token ;
			if(caso=="@f1")
			{
				if(!f1()) return false;
			}  
			else if(caso=="@f2")
			{
				if(!f2()) return false;
			} 
			else if(caso=="@f3a")
			{
				if(!f3a()) return false;
			} 
			else if(caso=="@f3b")
			{
				if(!f3b()) return false;
			} 
			else if(caso=="@f3c")
			{
				if(!f3c()) return false;
			} 
			else if(caso=="@f3d")
			{
				if(!f3d()) return false;
			} 
			else if(caso=="@f4")
			{
				if(!f4()) return false;
			} 
			else if(caso=="@f5a")
			{
				if(!f5a()) return false;
			}  
			else if(caso=="@f5b")
			{
				if(!f5b()) return false;
			} 
			else if(caso=="@f6a")
			{
				if(!f6a()) return false;
			} 
			else if(caso=="@f6b")
			{
				if(!f6b()) return false;
			}   
			else if(caso=="@f7")
			{
				if(!f7()) return false;
			} 
			else if(caso=="@f8a")
			{
				if(!f8a())return false;
			}  
			else if(caso=="@f8b")
			{
				if(!f8b())return false;
			}  
			else if(caso=="@f9a")
			{
				if(!f9a())return false;
			}  
			else if(caso=="@f9b")
			{
				if(!f9b())return false;
			}  
			else if(caso=="@f9c")
			{
				if(!f9c())return false;
			}  
			else if(caso=="@f9d")
			{
				if(!f9d())return false;
			}  
			else if(caso=="@f9e")
			{
				if(!f9e()) return false;
			}  
			else if(caso=="@f10a")
			{
				if(!f10a())return false;
			}  
			else if(caso=="@f10b")
			{
				if(!f10b()) return false;
			}  
			else if(caso=="@f10c")
			{
				if(!f10c()) return false;
			}  
			else if(caso=="@f11")
			{
				if(!f11()) return false;
			}  
			else if(caso=="@f12a")
			{
				if(!f12a()) return false;
			}  
			else if(caso=="@f12b")
			{
				if(!f12b()) return false;
			}  
			else if(caso=="@f13a")
			{
				if(!f13a()) return false;
			}  
			else if(caso=="@f13b")
			{
				if(!f13b()) return false;
			}
			else if(caso=="@f14")
			{
				if(!f14()) return false;
			}
			else if(caso=="@f15")
			{
				if(!f15()) return false;
			}
			else if(caso=="@f16a")
			{
				if(!f16a()) return false;
			}
			else if(caso=="@f16b")
			{
				if(!f16b()) return false;
			}
			else if(caso=="@f17a")
			{
				if(!f17a()) return false;
			}
			else if(caso=="@f17b")
			{
				if(!f17b()) return false;
			}
			else if(caso=="@f18")
			{
				if(!f18()) return false;
			}
			else if(caso=="@f20")
			{
				if(!f20()) return false;
			}
			else if(caso=="@f21a")
			{
				if(!f21a()) return false;
			}
			else if(caso=="@f21b")
			{
				if(!f21b()) return false;
			}
			else if(caso=="@f21c")
			{
				if(!f21c()) return false;
			}
			else if(caso=="@f21d")
			{
				if(!f21d()) return false;
			}
			else if(caso=="@f21e")
			{
				if(!f21e()) return false;
			}
			else if(caso=="@f21f")
			{
				if(!f21f()) return false;
			}
			else if(caso=="@f22a")
			{
				if(!f22a()) return false;
			}
			else if(caso=="@f22b")
			{
				if(!f22b()) return false;
			}
			else if(caso=="@f23a")
			{
				if(!f23a()) return false;
			}
			else if(caso=="@f23b")
			{
				if(!f23b()) return false;
			}
			else if(caso=="@f24a")
			{
				if(!f24a()) return false;
			}
			else if(caso=="@f24b")
			{
				if(!f24b()) return false;
			}
			else if(caso=="@f24c")
			{
				if(!f24c()) return false;
			}
			else if(caso=="@f25a")
			{
				if(!f25a()) return false;
			}
			else if(caso=="@f25b")
			{
				if(!f25b()) return false;
			}
			else if(caso=="@f25c")
			{
				if(!f25c()) return false;
			}
			else if(caso=="@f26")
			{
				if(!f26()) return false;
			}
			else if(caso=="@f28")
			{
				if(!f28()) return false;
			}
			else if(caso=="@f29a")
			{
				if(!f29a()) return false;
			}
			else if(caso=="@f29b")
			{
				if(!f29b()) return false;
			}
			else if(caso=="@f29c")
			{
				if(!f29c()) return false;
			}
			else if(caso=="@f30")
			{
				if(!f30()) return false;
			}
			pila.pop();
					
		}
		else
		{
			if(es_terminal(a.token))
			{  
				if(lista_tokens[i].first==a.token)
				{  
					i++;
					a.lexema=lista_tokens[i-1].second.first;
					if(a.token=="ID")
						ID_a.lexema=a.lexema;
					//cout<<"ESTO FALTABA: "<<a.token<<"\t"<<a.lexema<<endl;
					pila.pop();
				}
				else
				{  
					//cout<<"MAL "<<a.token<<endl;
 
					lista_errores_sintacticos.push_back(make_pair("ERROR: Caracter no esperado", make_pair(lista_tokens[i].second.first,lista_tokens[i].second.second)));
					pila.pop();
				}
			}
			else if(!es_terminal(a.token))
			{
				vector<atributos> b = busqueda_tabla(a, lista_tokens[i].first);
				if(b.size()==0)
				{
					lista_errores_sintacticos.push_back(make_pair("ERROR: Caracter no esperado", make_pair(lista_tokens[i].second.first ,lista_tokens[i].second.second)));
					i++;
					pila.pop();
				}
				else
				{	
					pila.pop();
					for(int i=b.size()-1;i>=0;i--)
					{
						//cout<<"ESTE: "<<b[i]<<endl;
						//cout<<"ESTO TIENE\t"<<b[i].token<<"\ttipo: "<<b[i].type<<"\tvalor: "<<b[i].value<<"\tlexema: "<<b[i].lexema <<						"\ttam: "<<b[i].tamanho<<"\tdireccion: "<<b[i].dir<<"\tcodigo: "<<b[i].codigo<<endl;
						pila.push(b[i]);
					}
				}
			}

		}
	
	}
}

int main()
{
PC_clave_Include_a.token= "PC_clave_Include"; 
PROGRAMA_a.token= "PROGRAMA";
PC_clave_main_a.token= "PC_clave_main";
Parentesis_Abierto_a.token= "Parentesis_Abierto";
Parentesis_Cerrado_a.token= "Parentesis_Cerrado";
Llave_Abierta_a.token= "Llave_Abierta";
lista_sentencias_a.token= "lista_sentencias";
PC_Clave_return_a.token= "PC_Clave_return";
Num_Entero_a.token= "Num_Entero";
Punto_Coma_a.token= "Punto_Coma";
Llave_Cerrada_a.token= "Llave_Cerrada";
sentencia_a.token= "sentencia";
e_a.token= "ε";
tipo_dato_a.token= "tipo_dato";
lista_def_a.token= "lista_def";
def_basica_a.token= "def_basica";
PC_Decl_int_a.token= "PC_Decl_int";
PC_Decl_float_a.token= "PC_Decl_float";
PC_Decl_double_a.token= "PC_Decl_double";
PC_Decl_bool_a.token= "PC_Decl_bool";
PC_Decl_char_a.token= "PC_Decl_char";
def_espec_a.token="def_espec";
lista_def1_a.token="lista_def1";
Coma_a.token="Coma";
ID_a.token="ID";
ID_a.type="KARELIA ESTUVO AQUI";
def_espec1_a.token="def_espec1";
acceso_array_a.token="acceso_array";
def_espec2_a.token="def_espec2";
simple_asign_a.token="simple_asign";
Corchete_Abierto_a.token="Corchete_Abierto";
Corchete_Cerrado_a.token="Corchete_Cerrado";
OP_Asignacion_Igual_a.token="OP_Asignacion_Igual";
sentencia1_a.token="sentencia1";
IF_ELSE_a.token="IF_ELSE";
WHILE_a.token="WHILE";
Num_Flotante_a.token="Num_Flotante";
F_a.token="F";
F1_a.token="F1";
T_a.token="T";
T1_a.token="T1";
E_a.token="E";
E1_a.token="E1";
W_a.token="W";
W1_a.token="W1";
operadores_a.token="operadores";
PC_Clave_while_a.token="PC_Clave_while";
condicion_a.token="condicion";
IF_a.token="IF";
IF_ELSE1_a.token="IF_ELSE1";
PC_Clave_if_a.token="PC_Clave_if";
PC_Clave_else_a.token="PC_Clave_else";
condicion_logica_a.token="condicion_logica";
condicion1_a.token="condicion1";
OP_Logico_And_a.token="OP_Logico_And";
OP_Logico_Or_a.token="OP_Logico_Or";
operadores_log_a.token="operadores_log";
OP_Relacional_Menor_a.token="OP_Relacional_Menor";
OP_Relacional_Menor_Igual_a.token="OP_Relacional_Menor_Igual";
OP_Relacional_Mayor_a.token="OP_Relacional_Mayor";
OP_Relacional_Mayor_Igual_a.token="OP_Relacional_Mayor_Igual";
OP_Relacional_Igual_a.token="OP_Relacional_Igual";
OP_Relacional_Diferente_a.token="OP_Relacional_Diferente";
op_aditivos_a.token="op_aditivos";
op_multiplicativos_a.token="op_multiplicativos";
OP_Aritmetico_Suma_a.token="OP_Aritmetico_Suma";
OP_Aritmetico_Resta_a.token="OP_Aritmetico_Resta";
OP_Aritmetico_Mult_a.token="OP_Aritmetico_Mult";
OP_Aritmetico_Div_a.token="OP_Aritmetico_Div";
OP_Aritmetico_Mod_a.token="OP_Aritmetico_Mod";
	ficheroSalida.open ("CodigoIntermedio.txt");
  metodoArchivo();
  for(int i=0; i<lista.size();i++)
  	cout<<lista[i].second<<"\t"<<lista[i].first<<endl;
  tokens();
  

  cout<<endl<<"LISTA DE TOKENS"<<endl;
  for(int i=0; i<lista_tokens.size();i++)
  	cout<<lista_tokens[i].second.second<<"\t"<<lista_tokens[i].second.first<<"\t"<<lista_tokens[i].first<<endl;


  cout<<endl<<"TABLA DE ERRORES"<<endl;
  for(int i=0; i<lista_errores.size();i++)
  	cout<<lista_errores[i].second.second<<"\t"<<lista_errores[i].second.first<<"\t"<<lista_errores[i].first<<endl;

map< string , campos >::iterator iter;
inicializa_tabla_simbolos();
/*  cout<<"TABLA DE SIMBOLOS"<<endl;
  for(iter=tabla_de_simbolos.begin(); iter!=tabla_de_simbolos.end();iter++)
  	cout<<iter->second.lexema<<"\t"<<iter->second.token<<"\t"<<iter->second.tipo<<"\t"<<iter->second.valor
  <<"\t"<<iter->second.dir<<endl;*/
  	//cout<<iter->first<<"\t"<<iter->second.token<<"\t"<<iter->second.tipo<<"\t"<<iter->second.valor<<endl;
  

cout<<endl<<"ANALISIS SINTACTICO"<<endl;
analisis_sintactico();
cout<<endl<<"TABLA DE ERRORES SINTACTICOS"<<endl;
  for(int i=0; i<lista_errores_sintacticos.size();i++)
  	cout<<lista_errores_sintacticos[i].second.second<<"\t"<<lista_errores_sintacticos[i].second.first<<"\t"<<lista_errores_sintacticos[i].first<<endl;
  cout<<endl;
ficheroSalida.close();
//map< string , campos >::iterator iter;
inicializa_tabla_simbolos();
  cout<<"TABLA DE SIMBOLOS"<<endl;
  cout<<"lexema"<<"\t"<<"token"<<"\t"<<"tipo"<<"\t"<<"valor" <<"\t"<<"dir ini"<<"\t"<<"dir fin"<<"\t"<<"tamanho"<<endl;
  for(iter=tabla_de_simbolos.begin(); iter!=tabla_de_simbolos.end();iter++)
  	cout<<iter->second.lexema<<"\t"<<iter->second.token<<"\t"<<iter->second.tipo<<"\t"<<iter->second.valor <<"\t"<<iter->second.dir-iter->second.tamanho<<"\t"<<iter->second.dir<<"\t"<<iter->second.tamanho<<endl;
  	//cout<<iter->first<<"\t"<<iter->second.token<<"\t"<<iter->second.tipo<<"\t"<<iter->second.valor<<endl;
  //cout<<"CHOSES "<<PROGRAMA_a.codigo<<endl;
  return 0;
}
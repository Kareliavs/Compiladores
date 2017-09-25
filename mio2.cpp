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

vector<pair< string ,  pair < string ,int > > > tabla_simbolos; 
stack<string> pila; 
struct campos {
        string token;
        int linea;
        string token_igual;
        string lexema_igual;
        basic_string<char>* direcccion;

};
struct terminales {
        vector< string >  PC_clave_Include;
        vector< string > PC_Decl_int;
        vector< string >  PC_Decl_float;
		vector< string > PC_Decl_double;
		vector< string >  PC_Decl_bool;
		vector< string >  PC_Decl_char;
		vector< string >  PC_clave_main;
		vector< string >  Parentesis_Abierto;
		vector< string >  Paretesis_Cerrado;
		vector< string >  Llave_Abierta;
		vector< string >  Llave_Cerrada;
		vector< string >  Corchete_Abierto;
		vector< string >  Corchete_Cerrado;
		vector< string >  Punto_Coma;
		vector< string >  Coma;
		vector< string >  OP_Asignacion_Igual;
		vector< string >  PC_Clave_return;
		vector< string >  Num_Entero;
		vector< string >  OP_Logico_And;
		vector< string >  OP_Logico_Or;
		vector< string >  OP_Relacional_Menor;
		vector< string >  OP_Relacional_Mayor;
		vector< string >  OP_Relacional_Mayor_Igual;
		vector< string >  OP_Relacional_Menor_Igual;
		vector< string >  OP_Relacional_Igual;
		vector< string >  OP_Relacional_Diferente;
		vector< string >  OP_Aritmetico_Suma;
		vector< string >  OP_Aritmetico_Resta;
		vector< string >  OP_Aritmetico_Mult;
		vector< string >  OP_Aritmetico_Div;
		vector< string >  OP_Aritmetico_Mod;
		vector< string >  ID;
		vector< string >  PC_Clave_if;
		vector< string >  PC_Clave_while;
        vector< string >  PC_Clave_else;
        vector< string >  Num_Flotante;
        vector< string >  $;
};
map< string , campos > tabla_de_simbolos;
///NO TERMINAL      TERMINAL  PRODUCCIoN 
map< string , terminales > tabla_sintactica;
map < string, string> tabla_sintactica_aux;

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
			lista_tokens.push_back(make_pair("Paretesis_Cerrado", make_pair(palabra.first ,palabra.second)));
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
   /*if(lista_tokens[i+1].first=="OP_Asignacion_Igual" and( lista_tokens[i+2].first=="Num_Entero" or lista_tokens[i+2].first== "Num_Flotante"
  				or lista_tokens[i+2].first=="Cadena" or lista_tokens[i+2].first=="ID" ) )
   {
   		a.token_igual=lista_tokens[i+2].first;
   		a.lexema_igual=lista_tokens[i+2].second.second;
   		cout<<"muere aqui if"<<endl;
   }
	*/
   
   //cout<<"ici"<<endl;
   if(lista_tokens[i].first=="ID")
   	tabla_de_simbolos.insert(std::pair<string, campos>(lista_tokens[i].second.first,a));
   //cout <<lista_tokens[i].second.first<<endl;
  }

}

void inicializa_tabla_sintactica()
{
	vector< string > aux;

	terminales PROGRAMA;
		aux.push_back("PC_clave_Include");
		aux.push_back("PROGRAMA");
		PROGRAMA.PC_clave_Include=aux;
		aux.clear();

		aux.push_back("PC_Decl_int");
		aux.push_back("PC_clave_main");
		aux.push_back("Parentesis_Abierto");
		aux.push_back("Paretesis_Cerrado");
		aux.push_back("Llave_Abierta");
		aux.push_back("lista_sentencias");
		aux.push_back("PC_Clave_return");
		aux.push_back("Num_Entero");  
		aux.push_back("Punto_Coma");
		aux.push_back("Llave_Cerrada");
		PROGRAMA.PC_Decl_int=aux;
		aux.clear();
	tabla_sintactica.insert(std::pair<string, terminales>("PROGRAMA",PROGRAMA));

	terminales lista_sentencias;
		aux.push_back("sentencia");
		aux.push_back("lista_sentencias");
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
		lista_sentencias.PC_Decl_float=aux;////cualquier numero
		aux.clear();

		aux.push_back("ε");
		lista_sentencias.Llave_Cerrada=aux;
		lista_sentencias.PC_Clave_return=aux;
		aux.clear();
	tabla_sintactica.insert(std::pair<string, terminales>("lista_sentencias",lista_sentencias));

	terminales def_basica;
		aux.push_back("ε");
		def_basica.Llave_Cerrada=aux;
		aux.clear();
	tabla_sintactica.insert(std::pair<string, terminales>("def_basica",def_basica));

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

}
void inicializa_pila()
{
	pila.push("$");
	pila.push("PROGRAMA");
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
|| a=="Paretesis_Cerrado"
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
vector<string> busqueda_tabla(string a, string token_actual)
{
	terminales baux =tabla_sintactica[a];
	if(token_actual=="PC_clave_main" )return baux.PC_clave_main;
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
	if(token_actual=="Paretesis_Cerrado")return baux.Paretesis_Cerrado;
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
void analisis_sintactico()
{
	inicializa_tabla_sintactica();
	inicializa_pila();
	int i=0;
	while(i<lista_tokens.size() and !pila.empty() )
	{
		string a=pila.top();
		cout<<"..."<<a<<endl;
		if(a=="ε")
		{  
			//i++;
			pila.pop();
		}
		else
		{
			if(es_terminal(a))
			{  
				if(lista_tokens[i].first==a)
				{  
					i++;
					pila.pop();
				}
				else
				{   
					lista_errores_sintacticos.push_back(make_pair("ERROR: Caracter no esperado", make_pair(a/*lista_tokens[i].second.first*/ ,lista_tokens[i].second.second)));
					pila.pop();
				}
			}
			else if(!es_terminal(a))
			{
				vector<string> b = busqueda_tabla(a, lista_tokens[i].first);
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
						pila.push(b[i]);
				}
			}

		}
	
	}
}

int main()
{
  metodoArchivo();
  for(int i=0; i<lista.size();i++)
  	cout<<lista[i].second<<"\t"<<lista[i].first<<endl;
  tokens();
  inicializa_tabla_simbolos();

  cout<<endl<<"LISTA DE TOKENS"<<endl;
  for(int i=0; i<lista_tokens.size();i++)
  	cout<<lista_tokens[i].second.second<<"\t"<<lista_tokens[i].second.first<<"\t"<<lista_tokens[i].first<<endl;


  cout<<endl<<"TABLA DE ERRORES"<<endl;
  for(int i=0; i<lista_errores.size();i++)
  	cout<<lista_errores[i].second.second<<"\t"<<lista_errores[i].second.first<<"\t"<<lista_errores[i].first<<endl;


  map< string , campos >::iterator iter;
  cout<<"TABLA DE SIMBOLOS"<<endl;
  for(iter=tabla_de_simbolos.begin(); iter!=tabla_de_simbolos.end();iter++)
  	cout<<iter->first<<"\t"<<iter->second.token_igual<<endl;

cout<<endl<<"ANALISIS SINTACTICO"<<endl;
analisis_sintactico();
cout<<endl<<"TABLA DE ERRORES SINTACTICOS"<<endl;
  for(int i=0; i<lista_errores_sintacticos.size();i++)
  	cout<<lista_errores_sintacticos[i].second.second<<"\t"<<lista_errores_sintacticos[i].second.first<<"\t"<<lista_errores_sintacticos[i].first<<endl;
  cout<<endl;
  return 0;
}
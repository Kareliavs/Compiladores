#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
using namespace std; 
///COMPILAR ASI ---->   g++ -std=c++0x mio.cpp -o a

char caracter = ' ';
vector<char> listarecorrido;
vector<pair < string ,int > > lista; 
			// token 		LEXEMAS   linea
vector<pair< string ,  pair < string ,int > > > lista_tokens; 
vector<pair< string ,  pair < string ,int > > > lista_errores; 
vector<pair< string ,  pair < string ,int > > > tabla_simbolos; 
vector<pair< 
				pair< 
					string,  				//TOKEN ID 
					pair < string ,int > 	// LEXEMA  // linea

				> ,
				pair< 
					string,  				//TOKEN char int float...
					pair < string , basic_string<char>* > 	//Lexema // direccion

				> 
			> 
		>tabla_simbolos_completa; 


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
	string cosita=palabra.first;
	int no_entra=0;
	//cout<<"cosita"<<cosita<<endl;
	if(palabra.first.size()==1)
	{   //cout<<"ESPACIO"<<endl;
		//cout<<"posible_salto:"<<palabra.first<<endl;
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
		palabra.first=aux;
		if(palabra.first =="" or palabra.first ==" " or palabra.first =="\n" ) ;
		else if (palabra.first[0] =='"')
			lista_tokens.push_back(make_pair("Cadena", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="main")
			lista_tokens.push_back(make_pair("PC_clave_main", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="char")
			lista_tokens.push_back(make_pair("PC_Decl_char", make_pair(palabra.first ,palabra.second)));
		else if (palabra.first =="float")
			lista_tokens.push_back(make_pair("PC_Decl_float", make_pair(palabra.first ,palabra.second)));
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

  			
				palabra1=palabra.first.substr(0,j);
				if (palabra1.size()>0)separar(make_pair(palabra1,palabra.second));
				signo= palabra.first.substr(j,1+cero);
				if (signo.size()>0)validacion(make_pair(signo,palabra.second));
				palabra2= palabra.first.substr(j+1+cero,palabra.first.size()-j-2-cero);
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
		separar(lista[i]);
		
  	//cout<<lista[i].second<<"\t"<<lista[i].first<<endl;
		//cout<<"palabra: "<<palabra<<"  signo:"<<signo<<endl;
	}
	for(int i=0; i<lis.size();i++)
	{   
		validacion2(lis[i]);
		
  	//cout<<lista[i].second<<"\t"<<lista[i].first<<endl;
		//cout<<"palabra: "<<palabra<<"  signo:"<<signo<<endl;
	}

}

int main()
{
  metodoArchivo();
  /*for(int i=0; i<lista.size();i++)
  	cout<<lista[i].second<<"\t"<<lista[i].first<<endl;*/
  tokens();
  // TODO
  /*
  tabla_simbolos.push_back(lista_tokens[0]);
  for(int i=1; i<lista_tokens.size();i++)
  { 
  	for(int j=0; j<tabla_simbolos.size();j++)
  		{   
  			if(lista_tokens[i].second.first==tabla_simbolos[j].second.first)
  				{	//cout<<"i: "<<i<<endl;
  					break;
  				}
  			if(j==tabla_simbolos.size()-1)
  				tabla_simbolos.push_back(lista_tokens[i]);
  		
  		}
  }


  */
  //SOLO ENTRAN VALIABLES
  tabla_simbolos.push_back(lista_tokens[0]);
  for(int i=1; i<lista_tokens.size();i++)
  { 
  	for(int j=0; j<tabla_simbolos.size();j++)
  		{   
  			if(lista_tokens[i].second.first==tabla_simbolos[j].second.first)
  				{	//cout<<"i: "<<i<<endl;
  					break;
  				}
  			if(j==tabla_simbolos.size()-1 and lista_tokens[i].first=="ID" /*(lista_tokens[i].first=="PC_Decl_char" or lista_tokens[i].first== "PC_Decl_float"
  				or lista_tokens[i].first=="PC_Decl_int" or lista_tokens[i].first=="PC_Decl_long")*/)
  				tabla_simbolos.push_back(lista_tokens[i]);
  		
  		}
  }
  for (int i =0; i< tabla_simbolos.size();i++)
  	for (int j=0; j< lista_tokens.size();j++)
  		if(tabla_simbolos[i]==lista_tokens[j])
  		{   
  			if(lista_tokens[j+1].first=="OP_Asignacion_Igual" and( lista_tokens[j+2].first=="Num_Entero" or lista_tokens[j+2].first== "Num_Flotante"
  				or lista_tokens[j+2].first=="Cadena" ) )
	  		{   
	  			auto* p = &tabla_simbolos[i].second.first ;
	  			//cout<<"DIRECCION "<<p;
	  			basic_string<char>* c2 = p;
	  			tabla_simbolos_completa.push_back
	  			(
	  				make_pair
	  				(
	  					tabla_simbolos[i], 
	  					make_pair
	  					(  	
	  						lista_tokens[j+2].first, 
	  						make_pair
	  						( 
	  							lista_tokens[j+2].second.first, 
	  							c2
	  						) 
						)
					)
				);
	  		}
	  		else 
	  		{
	  			lista_errores.push_back(make_pair("Warning: Variable no usada",tabla_simbolos[i].second));
	  		}


  		}	

  cout<<endl<<"LISTA DE LEXEMAS"<<endl;
  for(int i=0; i<lista_tokens.size();i++)
  	cout<<lista_tokens[i].second.second<<"\t"<<lista_tokens[i].second.first<<"\t"<<lista_tokens[i].first<<endl;


  cout<<endl<<"TABLA DE ERRORES"<<endl;
  for(int i=0; i<lista_errores.size();i++)
  	cout<<lista_errores[i].second.second<<"\t"<<lista_errores[i].second.first<<"\t"<<lista_errores[i].first<<endl;

  cout<<endl<<"TABLA DE SIMBOLOS"<<endl;
  for(int i=0; i<tabla_simbolos_completa.size();i++)
  	cout<<tabla_simbolos_completa[i].first.second.second<<"\t"<<tabla_simbolos_completa[i].first.second.first<<"\t"<<tabla_simbolos_completa[i].first.first<<
  	"\t"<<tabla_simbolos_completa[i].second.first<<"\t"<<tabla_simbolos_completa[i].second.second.first<<"\t"<<tabla_simbolos_completa[i].second.second.second<< endl;	
  
  cout<<endl;
  
  /*cout<<"TABLA DE SIMBOLOS"<<endl;
  for(int i=0; i<tabla_simbolos.size();i++)
  	cout<<tabla_simbolos[i].second.second<<"\t"<<tabla_simbolos[i].second.first<<"\t"<<tabla_simbolos[i].first<<endl;	*/
  return 0;
}
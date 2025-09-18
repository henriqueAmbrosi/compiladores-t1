#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TK_int 1
#define TK_float 2
#define TK_char 3
#define TK_struct 4
#define TK_if 5
#define TK_else 6


#define TK_id 7
#define TK_Abre_Colch 8
#define TK_Fecha_Colch 9
#define TK_Abre_Chaves 10
#define TK_Fecha_Chaves 11
#define TK_Fim_Arquivo 12
#define TK_Atrib 13
#define TK_Const_Int 14
#define TK_Mais 15
#define TK_Menos 16
#define TK_Mult 17
#define TK_Abre_Par 18
#define TK_Fecha_Par 19
#define TK_virgula 20
#define TK_pv 21
#define TK_Maior 22
#define TK_Menor 23
#define TK_Menor_Igual 24
#define TK_Maior_Igual 25
#define TK_Igual 26
#define TK_Diferente 27
#define TK_while 28
#define TK_and_bitwise 29
#define TK_and_logico 30
#define TK_or_logico 31
#define TK_do 32
#define TK_for 33


/***********************************************************************************/
/*                                                                                 */
/*  IN�CIO DO L�XICO - N�o entre a n�o ser que tenha interesse pessoal em l�xicos  */
/*                                                                                 */
/***********************************************************************************/


int linlex = 0, collex = 1;


char tokens[][20] = {"", "TK_int",
                     "TK_float",
                     "TK_char",
                     "TK_struct",
                     "TK_if",
                     "TK_else",
                     "TK_id",
                     "TK_Abre_Colch",
                     "TK_Fecha_Colch",
                     "TK_Abre_Chaves",
                     "TK_Fecha_Chaves",
                     "TK_Fim_Arquivo",
                     "TK_Atrib",
                     "TK_Const_Int",
                     "TK_Mais",
                     "TK_Menos",
                     "TK_Mult",
                     "TK_Abre_Par",
                     "TK_Fecha_Par",
                     "TK_virgula",
                     "TK_pv",
                     "TK_Maior",
                     "TK_Menor",
                     "TK_Menor_Igual",
                     "TK_Maior_Igual",
                     "TK_Igual",
                     "TK_Diferente",
                     "TK_while",
                     "TK_and_bitwise",
                     "TK_and_logico",
                     "TK_or_logico",
                     "TK_do",
                     "TK_for",
                  };


typedef struct pal
{
   char palavra[20];
   int token;
} tpal;
tpal reservadas[] = {{"", 0},
                     {"int", TK_int},
                     {"float", TK_float},
                     {"char", TK_char},
                     {"struct", TK_struct},
                     {"if", TK_if},
                     {"else", TK_else},
                     {"while", TK_while},
                     {"do", TK_do},
                     {"for", TK_for},
                     {"fim", -1}};


FILE *arqin;
int token;
char lex[20];
char c;
// vari�veis do marca - restaura


int tokenant;
long posarq;
char lexant[100];
char cant;
int marcou = 0;


void marca_pos()
{
   marcou = 1;
   tokenant = token;
   posarq = ftell(arqin);
   strcpy(lexant, lex);
   cant = c;
}


void restaura()
{
   fseek(arqin, posarq, SEEK_SET);
   token = tokenant;
   strcpy(lex, lexant);
   c = cant;
}


char le_char()
{
   if (fread(&c, 1, 1, arqin) == 0)
      return -1;
   if (c == '\n')
   {
      linlex++;
      collex = 1;
   }
   else
      collex++;
   return c;
};


int pal_res(char lex[])
{
   int tk = 0;
   while (strcmp(reservadas[tk].palavra, "fim") != 0)
   {
      if (strcmp(lex, reservadas[tk].palavra) == 0)
         return reservadas[tk].token;
      tk++;
   }
   return TK_id;
}


int le_token()
{
   static int pos = 0;
   static int estado = 0;
   while (1)
   {
      switch (estado)
      {
      case 0:
         if (c == ',')
         {
            c = le_char();
            return TK_virgula;
         }
         if (c == '+')
         {
            c = le_char();
            return TK_Mais;
         }
         if (c == '-')
         {
            c = le_char();
            return TK_Menos;
         }
         if (c == '*')
         {
            c = le_char();
            return TK_Mult;
         }
         if (c == '{')
         {
            c = le_char();
            return TK_Abre_Chaves;
         }
         if (c == '}')
         {
            c = le_char();
            return TK_Fecha_Chaves;
         }
         if (c == ';')
         {
            c = le_char();
            strcpy(lex, ";");
            return TK_pv;
         }
         if (c == '[')
         {
            c = le_char();
            return TK_Abre_Colch;
         }
         if (c == ']')
         {
            c = le_char();
            return TK_Fecha_Colch;
         }
         if (c == '(')
         {
            c = le_char();
            return TK_Abre_Par;
         }
         if (c == ')')
         {
            c = le_char();
            return TK_Fecha_Par;
         }
         if (c == '=')
         {
            c = le_char();
            if (c == '=')
            {
               c = le_char();
               return TK_Igual;
            }
            strcpy(lex, "=");
            return TK_Atrib;
         }
         if (c == '<')
         {
            c = le_char();
            if (c == '=')
            {
               c = le_char();
               return TK_Menor_Igual;
            }
            return TK_Menor;
         }
         if (c == '&')
         {
            c = le_char();
            if (c == '&')
            {
               c = le_char();
               return TK_and_logico;
            }
            return TK_and_bitwise;
         }
         if (c == '>')
         {
            c = le_char();
            if (c == '=')
            {
               c = le_char();
               return TK_Maior_Igual;
            }
            return TK_Maior;
         }
         if (c == '!')
         {
            c = le_char();
            if (c == '=')
            {
               c = le_char();
               return TK_Diferente;
            }
         }
         if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_')
         {
            lex[0] = c;
            c = le_char();
            pos = 1;
            estado = 1;
            break;
         }
         if (c >= '0' && c <= '9')
         {
            lex[0] = c;
            c = le_char();
            pos = 1;
            estado = 2;
            break;
         }
         if (c == -1)
            return TK_Fim_Arquivo;
         if (c == '\n' || c == '\r' || c == '\t' || c == '\0' || c == ' ')
         {
            c = le_char();
            break;
         }
      case 1:
         if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9')
         {
            lex[pos++] = c;
            c = le_char();
            break;
         }
         else
         {
            estado = 0;
            lex[pos] = '\0';
            return pal_res(lex);
         }
      case 2:
         if (c >= '0' && c <= '9')
         {
            lex[pos++] = c;
            c = le_char();
            break;
         }
         else
         {
            estado = 0;
            lex[pos] = '\0';
            return TK_Const_Int;
         }
      }
   }
}


/********************/
/*                  */
/*  FIM DO L�XICO   */
/*                  */
/********************/


#define MAX_COD 1000


void mostra_t()
{
   printf("%s lex=%s na lin %d, col %d\n", tokens[token], lex, linlex, collex);
}


void geralabel(char label[])
{
   static int numlabel = 0;
   sprintf(label, "LB%03d", numlabel++);
}


void geratemp(char temp[])
{
   static int numtemp = 0;
   sprintf(temp, "T%03d", numtemp++);
}


/****************/
/*              */
/*  EXPRESS�ES  */
/*              */
/****************/


int MultiplicativeExpression(char T_p[MAX_COD], char T_c[MAX_COD]);
int MultiplicativeExpressionRest(char S_hp[MAX_COD], char S_sp[MAX_COD], char S_hc[MAX_COD], char S_sc[MAX_COD]);
int AdditiveExpression(char E_p[MAX_COD], char E_c[MAX_COD]);
int AdditiveExpressionRest(char R_hp[MAX_COD], char R_sp[MAX_COD], char R_hc[MAX_COD], char R_sc[MAX_COD]);
int PrimaryExpression(char F_p[MAX_COD], char F_c[MAX_COD]);
int RelationalExpression(char E_p[MAX_COD], char E_c[MAX_COD]);
int RelationalExpressionRest(char R_hp[MAX_COD], char R_sp[MAX_COD], char R_hc[MAX_COD], char R_sc[MAX_COD]);
int AssignmentExpression(char A_p[MAX_COD], char A_c[MAX_COD]);
int Command(char Com_c[MAX_COD]);
int CommandList(char Com_c[MAX_COD]);
int Expression(char e_p[MAX_COD], char e_c[MAX_COD]);

int AssignmentExpression(char A_p[MAX_COD], char A_c[MAX_COD]){
   char A1_c[MAX_COD], A1_p[MAX_COD]; 
   marca_pos();
   if(token == TK_id){
      strcpy(A_p, lex);
      token = le_token();
      if(token == TK_Atrib){
         token = le_token();
         if(AssignmentExpression(A1_p, A1_c)){
            sprintf(A_c, "%s\t%s = %s\n", A1_c, A_p, A1_p);
            return 1;
         }
      }
   }
   restaura();
   if(RelationalExpression(A_p, A_c)){
      return 1;
   }

   return 0;
}

int RelationalExpression(char E_p[MAX_COD], char E_c[MAX_COD])
{
   char T_p[MAX_COD], T_c[MAX_COD], R_hp[MAX_COD], R_sp[MAX_COD], R_hc[MAX_COD], R_sc[MAX_COD];

   if (AdditiveExpression(T_p, T_c))
   {
      strcpy(R_hc, T_c);
      strcpy(R_hp, T_p);
      if (RelationalExpressionRest(R_hp, R_sp, R_hc, R_sc))
      {
         strcpy(E_c, R_sc);
         strcpy(E_p, R_sp);
         return 1;
      }
   }
   return 0;
}

int RelationalExpressionRest(char R_hp[MAX_COD], char R_sp[MAX_COD], char R_hc[MAX_COD], char R_sc[MAX_COD])
{
   char T_c[MAX_COD], R1_hc[MAX_COD], R1_sc[MAX_COD], T_p[MAX_COD], R1_hp[MAX_COD], R1_sp[MAX_COD];
   if (token == TK_Maior)
   {
      token = le_token();
      if (AdditiveExpression(T_p, T_c))
      {
         geratemp(R1_hp);
         sprintf(R1_hc, "%s%s\t%s=%s>%s\n", R_hc, T_c, R1_hp, R_hp, T_p);
         if (RelationalExpressionRest(R1_hp, R1_sp, R1_hc, R1_sc))
         {
            strcpy(R_sp, R1_sp);
            strcpy(R_sc, R1_sc);
            return 1;
         }
      }
      return 0;
   }
   if (token == TK_Menor)
   {
      token = le_token();
      if (AdditiveExpression(T_p, T_c))
      {
         geratemp(R1_hp);
         sprintf(R1_hc, "%s%s\t%s=%s<%s\n", R_hc, T_c, R1_hp, R_hp, T_p);
         if (RelationalExpressionRest(R1_hp, R1_sp, R1_hc, R1_sc))
         {
            strcpy(R_sp, R1_sp);
            strcpy(R_sc, R1_sc);
            return 1;
         }
      }
      return 0;
   }
   strcpy(R_sp, R_hp);
   strcpy(R_sc, R_hc);
   return 1;
}

// E -> E1 + T {E.cod=....}
// E -> T { Rhp=Tp   Rhc=Tc}  R   {E.p=RSp   E.c=Rsc}


int AdditiveExpression(char E_p[MAX_COD], char E_c[MAX_COD])
{
   char T_p[MAX_COD], T_c[MAX_COD], R_hp[MAX_COD], R_sp[MAX_COD], R_hc[MAX_COD], R_sc[MAX_COD];
   if (MultiplicativeExpression(T_p, T_c))
   {
      strcpy(R_hc, T_c);
      strcpy(R_hp, T_p);
      if (AdditiveExpressionRest(R_hp, R_sp, R_hc, R_sc))
      {
         strcpy(E_c, R_sc);
         strcpy(E_p, R_sp);
         return 1;
      }
   }
   return 0;
}


int AdditiveExpressionRest(char R_hp[MAX_COD], char R_sp[MAX_COD], char R_hc[MAX_COD], char R_sc[MAX_COD])
{
   char T_c[MAX_COD], R1_hc[MAX_COD], R1_sc[MAX_COD], T_p[MAX_COD], R1_hp[MAX_COD], R1_sp[MAX_COD];
   if (token == TK_Mais)
   {
      token = le_token();
      if (MultiplicativeExpression(T_p, T_c))
      {
         geratemp(R1_hp);
         // gen(+,R1hp,Rhp,Tp)
         sprintf(R1_hc, "%s%s\t%s=%s+%s\n", R_hc, T_c, R1_hp, R_hp, T_p);
         if (AdditiveExpressionRest(R1_hp, R1_sp, R1_hc, R1_sc))
         {
            strcpy(R_sp, R1_sp);
            strcpy(R_sc, R1_sc);
            return 1;
         }
      }
      return 0;
   }
   if (token == TK_Menos)
   {
      token = le_token();
      if (MultiplicativeExpression(T_p, T_c))
      {
         geratemp(R1_hp);
         sprintf(R1_hc, "%s%s\t%s=%s-%s\n", R_hc, T_c, R1_hp, R_hp, T_p);
         if (AdditiveExpressionRest(R1_hp, R1_sp, R1_hc, R1_sc))
         {
            strcpy(R_sp, R1_sp);
            strcpy(R_sc, R1_sc);
            return 1;
         }
      }
      return 0;
   }
   strcpy(R_sp, R_hp);
   strcpy(R_sc, R_hc);
   return 1;
}


int MultiplicativeExpression(char T_p[MAX_COD], char T_c[MAX_COD])
{
   char F_c[MAX_COD], F_p[MAX_COD], S_hp[MAX_COD], S_sp[MAX_COD], S_hc[MAX_COD], S_sc[MAX_COD];
   if (PrimaryExpression(F_p, F_c))
   {
      strcpy(S_hc, F_c);
      strcpy(S_hp, F_p);
      if (MultiplicativeExpressionRest(S_hp, S_sp, S_hc, S_sc))
      {
         strcpy(T_c, S_sc);
         strcpy(T_p, S_sp);
         return 1;
      }
   }
   return 0;
}


int MultiplicativeExpressionRest(char S_hp[MAX_COD], char S_sp[MAX_COD], char S_hc[MAX_COD], char S_sc[MAX_COD])
{
   char F_c[MAX_COD], S1_hc[MAX_COD], S1_sc[MAX_COD], F_p[MAX_COD], S1_hp[MAX_COD], S1_sp[MAX_COD];
   if (token == TK_Mult)
   {
      token = le_token();
      if (PrimaryExpression(F_p, F_c))
      {
         geratemp(S1_hp);
         sprintf(S1_hc, "%s%s\t%s=%s*%s\n", S_hc, F_c, S1_hp, S_hp, F_p);
         if (MultiplicativeExpressionRest(S1_hp, S1_sp, S1_hc, S1_sc))
         {
            strcpy(S_sp, S1_sp);
            strcpy(S_sc, S1_sc);
            return 1;
         }
      }
      return 0;
   }
   strcpy(S_sp, S_hp);
   strcpy(S_sc, S_hc);
   return 1;
}
// F->id
// F->cte
// F->(E)
int PrimaryExpression(char F_p[MAX_COD], char F_c[MAX_COD])
{


   if (token == TK_Const_Int)
   {
      geratemp(F_p);
      sprintf(F_c, "\t%s = %s\n", F_p, lex);
      token = le_token();
      return 1;
   }
   if (token == TK_id)
   {
      strcpy(F_c, "");
      strcpy(F_p, lex);
      token = le_token();
      return 1;
   }
   if (token == TK_Abre_Par)
   {
      char E_c[MAX_COD], E_p[MAX_COD];
      token = le_token();
      if (AssignmentExpression(E_p, E_c))
         if (token == TK_Fecha_Par)
         {
            token = le_token();
            strcpy(F_c, E_c);
            strcpy(F_p, E_p);
            return 1;
         }
         else
         {
            printf("Erro!!! Esperava fecha par�nteses\n");
            return 0;
         }
   }


   return 0;
}


int ComposedExpression(char Comp_c[MAX_COD])
{
   char Com_cod[MAX_COD];
   if (token == TK_Abre_Chaves)
   {
      token = le_token();
      if (token == TK_Fecha_Chaves)
      {
         token = le_token();
         Comp_c[0] = '\0';
         return 1;
      }


      if (CommandList(Com_cod))
      {
         if (token == TK_Fecha_Chaves)
         {
            token = le_token();
            sprintf(Comp_c, "%s", Com_cod);
            return 1;
         }
      }


     
   }
   return 0;
}


int IfExpression(char If_c[MAX_COD])
{
   char labelFinal[MAX_COD], labelElse[MAX_COD];
   geralabel(labelFinal);
   geralabel(labelElse);
   if (token == TK_if)
   {
      token = le_token();
      if (token == TK_Abre_Par)
      {
         token = le_token();
         char E_p[MAX_COD], E_cod[MAX_COD];
         if (Expression(E_p, E_cod))
         {
            if (token == TK_Fecha_Par)
            {
               token = le_token();
               char E2_cod[MAX_COD];
               if (Command(E2_cod))
               {
                  sprintf(If_c, "\tif %s == 0\n", E_p);
                  sprintf(If_c, "%s\tgoto %s\n", If_c, labelElse);
                  sprintf(If_c, "%s%s", If_c, E2_cod);
                  sprintf(If_c, "%s\tgoto %s\n", If_c, labelFinal);
                  sprintf(If_c, "%s%s:\n", If_c, labelElse);
                  if (token == TK_else)
                  {
                     token = le_token();


                     char E3_cod[MAX_COD];
                     if (Command(E3_cod))
                     {


                        sprintf(If_c, "%s%s", If_c, E3_cod);
                        sprintf(If_c, "%s%s:\n", If_c, labelFinal);
                        return 1;
                     }
                  }
                  sprintf(If_c, "%s%s:\n", If_c, labelFinal);
                  return 1;
               }
            }
         }
      }
   }


   return 0;
}


int WhileExpression(char Com_c[MAX_COD])
{
   char labelFinal[MAX_COD], labelLaco[MAX_COD];
   geralabel(labelFinal);
   geralabel(labelLaco);
   if (token == TK_while)
   {
      token = le_token();
      if (token == TK_Abre_Par)
      {
         token = le_token();
         char E_p[MAX_COD], E_cod[MAX_COD];
         if (Expression(E_p, E_cod))
         {
            if (token == TK_Fecha_Par)
            {
               token = le_token();
               char E2_cod[MAX_COD];
               if (Command(E2_cod))
               {
                  sprintf(Com_c, "%s:%s == 0\n", labelLaco, E_p);
                  sprintf(Com_c, "%s\tgoto %s\n", Com_c, labelFinal);
                  sprintf(Com_c, "%sif %s == 0", Com_c, E2_cod);
                  sprintf(Com_c, "%s\tgoto %s\n", Com_c, labelLaco);
                  sprintf(Com_c, "%s%s:\n", Com_c, labelFinal);
                  return 1;
               }
            }
         }
      }
   }
   return 0;
}


int CommandExpression(char Com_p[MAX_COD], char Com_c[MAX_COD])
{
   char E_p[MAX_COD], E_cod[MAX_COD];


    if (token == TK_pv)
   {
      token = le_token();
      return 1;
   }


   if (Expression(E_p, E_cod))
   {
      if (token == TK_pv)
      {
         token = le_token();
         strcpy(Com_p, E_p);
         sprintf(Com_c, "%s", E_cod);
         return 1;
      }
   }
 


   return 0;
}

int Expression(char e_p[MAX_COD], char e_c[MAX_COD]){
   char e1_c[MAX_COD];
   if(AssignmentExpression(e_p, e_c)){
      if(token == TK_virgula){
         token = le_token();
         if(Expression(e_p, e1_c)){
            sprintf(e_c, "%s\n%s", e_c, e1_c);
            return 1;
         }

         return 0;
      }

      return 1;
   }

   return 0;
}


int CommandList(char Com_c[MAX_COD]){
   char Command_c[MAX_COD], CommandList_c[MAX_COD];
   if(Command(Command_c)){
      sprintf(Com_c, "%s", Command_c);
      marca_pos();
      if(CommandList(CommandList_c)){
         sprintf(Com_c, "%s%s", Com_c, CommandList_c);
         return 1;
      }
      restaura();
      return 1;
   }
   
   return 0;


}

int ForExpression(char Com_c[MAX_COD]){
   char labelFinal[MAX_COD], labelCondicao[MAX_COD], labelContinue[MAX_COD], command_c[MAX_COD], ce1_p[MAX_COD], ce1_c[MAX_COD], ce2_p[MAX_COD], ce2_c[MAX_COD], e_p[MAX_COD], e_c[MAX_COD];
   geralabel(labelFinal);
   geralabel(labelCondicao);
   geralabel(labelContinue);

   if(token == TK_for){
      token = le_token();
      if(token == TK_Abre_Par){
         token = le_token();
         if(CommandExpression(ce1_p, ce1_c)){
            if(CommandExpression(ce2_p, ce2_c)){

               if(token == TK_Fecha_Par){
                  token = le_token();
                  if(Command(command_c)){
                     sprintf(Com_c, "%s", ce1_c);
                     sprintf(Com_c, "%s\tgoto %s\n", Com_c, labelCondicao);
                     sprintf(Com_c, "%s%s:\n", Com_c, labelContinue);
                     // sprintf(Com_c, "%s%s", Com_c, e_c); Sem expressão para rodar a cada iteração
                     sprintf(Com_c, "%s%s:\n", Com_c, labelCondicao);
                     sprintf(Com_c, "%s%s", Com_c, ce2_c);
                     
                     // Implementa os laços infinitos
                     if(strlen(ce2_p) != 0){
                        sprintf(Com_c, "%s\tif %s == 0\n", Com_c, ce2_p);
                        sprintf(Com_c, "%s\tgoto %s\n", Com_c, labelFinal);
                     }

                     sprintf(Com_c, "%s%s\n", Com_c, command_c);
                     sprintf(Com_c, "%s\tgoto %s\n", Com_c, labelContinue);
                     sprintf(Com_c, "%s%s:\n", Com_c, labelFinal);


                     return 1;
                  }
               }

               if(Expression(e_p, e_c)){
                  if(token == TK_Fecha_Par){
                     token = le_token();
                     if(Command(command_c)){
                        sprintf(Com_c, "%s", ce1_c);
                        sprintf(Com_c, "%s\tgoto %s\n", Com_c, labelCondicao);
                        sprintf(Com_c, "%s%s:\n", Com_c, labelContinue);
                        sprintf(Com_c, "%s%s", Com_c, e_c);
                        sprintf(Com_c, "%s%s:\n", Com_c, labelCondicao);
                        sprintf(Com_c, "%s%s", Com_c, ce2_c);
                        // Implementa os laços infinitos
                        if(strlen(ce2_p) != 0){
                           sprintf(Com_c, "%s\tif %s == 0\n", Com_c, ce2_p);
                           sprintf(Com_c, "%s\tgoto %s\n", Com_c, labelFinal);
                        }
                        sprintf(Com_c, "%s%s", Com_c, command_c);
                        sprintf(Com_c, "%s\tgoto %s\n", Com_c, labelContinue);
                        sprintf(Com_c, "%s%s:\n", Com_c, labelFinal);

                        return 1;
                     }
                  }
               }
            }
         }
      }
   }

   return 0;
}


int Command(char Com_c[MAX_COD])
{
   // if(token == TK_do) return ComDoWhile else
   if (token == TK_if)
      return IfExpression(Com_c);
   else if (token == TK_Abre_Chaves)
      return ComposedExpression(Com_c);
   else if (token == TK_while)
      return WhileExpression(Com_c);
   else if (token == TK_for)
      return ForExpression(Com_c);


   char Com_p[MAX_COD];
   return CommandExpression(Com_p, Com_c);
}


int main()
{
   FILE *arqout;
   char Com_c[MAX_COD];
   if ((arqin = fopen("./prog.cpp", "rt")) == NULL)
   {
      printf("Erro na abertura do arquivo");
      exit(0);
   }
   if ((arqout = fopen("./saida.kvmp", "wt")) == NULL)
   {
      printf("Erro na abertura do arquivo de saida");
      exit(0);
   }
   token = le_token();
   char If_cod[MAX_COD];
   if (Command(If_cod) == 0)
      printf("Erro no comando!!!\n");
   else
   {
      printf("%s\n", If_cod);
      fprintf(arqout, "%s\n", If_cod);
   }
   fclose(arqin);
   fclose(arqout);
   // system("pause");
}





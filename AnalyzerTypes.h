#ifndef AnalyzerTypes
#define AnalyzerTypes

typedef enum
{
    ERROR,
    IDENTIFIER,
    INTEGER_NUMBER,
    ASSIGNMENT,
    WHILE,
    EOS,
    AND,
    BEGIN,
    BOOLEAN,
    CHAR,
    DO,
    ELSE,
    END,
    FALSE,
    IF,
    INTEGER,
    MOD,
    NOT,
    OR,
    PROGRAM,
    READ,
    REAL,
    THEN,
    TRUE,
    WRITE,
    OPEN_PARENTHESES,
    CLOSE_PARENTHESES,
    DOT,
    SEMICOLON,
    COMMA,
    SUBTRACTION,
    ADDITION,
    DIVISION,
    MULTIPLICATION,
    RELATIONAL_OPERATOR,
    COMMENT,
    REAL_NUMBER,
    CHARACTER
} TAtom;

typedef enum
{
    LT,
    LE,
    EQ,
    NE,
    GT,
    GE,
} TRelationalOperator;

typedef struct
{
    TAtom atom;
    int line;
    int integerAttribute;
    char idAttribute[15];
    double doubleAttribute;
    char charAttribute;
    TRelationalOperator relationalOperator;
} TInformationAtom;

#endif
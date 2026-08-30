
#include "TokenStream.h"

#include "Constants.h"
#include "Error.h"

#include <cctype>
#include <string>

Token_stream::Token_stream(std::istream& input)
    : input{input}{
}

void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into a full buffer");

    buffer = t;
    full = true;
}

void Token_stream::ignore(char c1, char c2) {
    if (full && (buffer.kind == c1 || buffer.kind == c2)) {
        full = false;
        return;
    }
    full = false;
    char ch = 0;
    while (input >> ch) {
        if (ch == c1 || ch == c2)
            return;
    }
}

//returns operations into token stream and assigns numbers to value and keys to string
Token Token_stream::get()
{
    if (full) {
        full = false;
        return buffer;
    }

    char ch;
    input >> ch;

    switch (ch) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    case '{':
    case '}':
    case print:
    case printc:
    case quit:
    case '!':
    case '%':
    case ',':
    case let:
        return Token{ ch };

    default:
        if (std::isdigit(ch)) {
            input.putback(ch);

            double val;
            input >> val;

            return Token{ number, val };
        }

        if (std::isalpha(ch)) {
            std::string s;
            s += ch;
            while (input.get(ch) && (isalpha(ch) || isdigit(ch))) {
                if (!std::isalpha(ch) && !std::isdigit(ch))
                    break;

                s += ch;
            }

            if (input) {
                input.putback(ch);
            }

            if (s == sqrtkey) {
                return Token{ sqrt_key };
            }

            if (s == powkey) {
                return Token{ pow_key };
            }

            if (s == quitkey) {
                return Token{ quit };
            }

            return Token{ name, s };
        }
        error("Bad token");
    }
}

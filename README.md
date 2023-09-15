# Minishell

## Links

## Posix Rules to Know

### Expand

- 2.6 Word Expansions

>The '\$' character is used to introduce parameter expansion, command substitution, or arithmetic evaluation. If an unquoted '\$' is followed by a character that is not one of the following:
> - A numeric character
> - The name of one of the special parameters (see Special Parameters)
> - A valid first character of a variable name
> - A \<left-curly-bracket> ( '\{' )
> - A \<left-parenthesis>
>the result is unspecified.
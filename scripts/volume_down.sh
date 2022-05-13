amixer sset Line $(($(amixer sget Line | grep '^\ *Front Left' | sed -e 's/^[^\[]*\[//' -e 's/%.*$//')-1))%

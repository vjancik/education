
# testuje spravnou sekvenci cislovani akci a format vystupu (pouze syntax)
# bez zaruky, muze obsahovat chyby

outf="h2o.out"

tr -d " \t" < ${outf} > $$

# test cislovani akci
# tiskne radky s chybnym cislovanim
cat $$ | awk -F":" ' { c++; if (c != $1) print NR, " => ", $1, " : chyba v cislovani akci"; } '


# kontrola sytaxe vystupu
# vytiskne radky, ktere neodpovidaji formatu vytupu
echo "=== radky, ktere neodpovidaji formatu vystupu"

cat $$ | sed '/^[1-9][0-9]*:H[1-9][0-9]*:started$/d
/^[1-9][0-9]*:H[1-9][0-9]*:waiting$/d
/^[1-9][0-9]*:H[1-9][0-9]*:ready$/d
/^[1-9][0-9]*:H[1-9][0-9]*:beginbonding$/d
/^[1-9][0-9]*:H[1-9][0-9]*:bonded$/d
/^[1-9][0-9]*:H[1-9][0-9]*:finished$/d
/^[1-9][0-9]*:O[1-9][0-9]*:started$/d
/^[1-9][0-9]*:O[1-9][0-9]*:waiting$/d
/^[1-9][0-9]*:O[1-9][0-9]*:ready$/d
/^[1-9][0-9]*:O[1-9][0-9]*:beginbonding$/d
/^[1-9][0-9]*:O[1-9][0-9]*:bonded$/d
/^[1-9][0-9]*:O[1-9][0-9]*:finished$/d
'


# kontrola chybejicich vystupu
# tiskne informaci, ktery text ve vystupu chybi
function check_missing() {
    t=$1
    cat $$ | grep '^[1-9][0-9]*:'${t}'[1-9][0-9]*:started$' >/dev/null || echo "${t} started"
    cat $$ | grep '^[1-9][0-9]*:'${t}'[1-9][0-9]*:waiting$' >/dev/null || echo "${t} waiting"
    cat $$ | grep '^[1-9][0-9]*:'${t}'[1-9][0-9]*:beginbonding$' >/dev/null || echo "${t} begin bonding"
    cat $$ | grep '^[1-9][0-9]*:'${t}'[1-9][0-9]*:bonded$' >/dev/null || echo "${t} bonded"
    cat $$ | grep '^[1-9][0-9]*:'${t}'[1-9][0-9]*:finished$' >/dev/null || echo "${t} finished"
}

echo "=== chybejici vystupy"
echo "** poznamka: \"O waiting\" nemusi nutne znamenat chybu, muze se stat, ze oxygen bude vzdy posledni, kdo vstupuje do molekuly"

check_missing "H"
check_missing "O"

rm $$

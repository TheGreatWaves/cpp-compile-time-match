#include "../comptrie.hpp"
#include "../external/nanobench/nanobench.h"

constexpr int EPOCHS = 100;
constexpr int EPOCH_ITERATIONS = 10000;
auto words_52_characters_1()
{
    std::string str = "z";
    std::string s;
    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("5 unique letters - match", [&] {
          match(str) s = "";
          case("a") s = "a";
          case("b") s = "b";
          case("c") s = "c";
          case("d") s = "d";
          case("e") s = "e";
          case("f") s = "f";
          case("g") s = "g";
          case("h") s = "h";
          case("i") s = "i";
          case("j") s = "j";
          case("k") s = "k";
          case("l") s = "l";
          case("m") s = "m";
          case("n") s = "n";
          case("o") s = "o";
          case("p") s = "p";
          case("q") s = "q";
          case("r") s = "r";
          case("s") s = "s";
          case("t") s = "t";
          case("u") s = "u";
          case("v") s = "v";
          case("w") s = "w";
          case("x") s = "x";
          case("y") s = "y";
          case("z") s = "z";
          case("a") s = "a";
          case("b") s = "b";
          case("c") s = "c";
          case("d") s = "d";
          case("e") s = "e";
          case("f") s = "f";
          case("g") s = "g";
          case("h") s = "h";
          case("i") s = "i";
          case("j") s = "j";
          case("k") s = "k";
          case("l") s = "l";
          case("m") s = "m";
          case("n") s = "n";
          case("o") s = "o";
          case("p") s = "p";
          case("q") s = "q";
          case("r") s = "r";
          case("s") s = "s";
          case("t") s = "t";
          case("u") s = "u";
          case("v") s = "v";
          case("w") s = "w";
          case("x") s = "x";
          case("y") s = "y";
          case("z") s = "z";
          endmatch;
        });

    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("5 unique letters - if", [&] {
          if (str == "a") s = "a";
          else if (str == "b") s = "b";
          else if (str == "c") s = "c";
          else if (str == "d") s = "d";
          else if (str == "e") s = "e";
          else if (str == "f") s = "f";
          else if (str == "g") s = "g";
          else if (str == "h") s = "h";
          else if (str == "i") s = "i";
          else if (str == "j") s = "j";
          else if (str == "k") s = "k";
          else if (str == "l") s = "l";
          else if (str == "m") s = "m";
          else if (str == "n") s = "n";
          else if (str == "o") s = "o";
          else if (str == "p") s = "p";
          else if (str == "q") s = "q";
          else if (str == "r") s = "r";
          else if (str == "s") s = "s";
          else if (str == "t") s = "t";
          else if (str == "u") s = "u";
          else if (str == "v") s = "v";
          else if (str == "w") s = "w";
          else if (str == "x") s = "x";
          else if (str == "y") s = "y";
          else if (str == "z") s = "z";
          else if (str == "a") s = "a";
          else if (str == "b") s = "b";
          else if (str == "c") s = "c";
          else if (str == "d") s = "d";
          else if (str == "e") s = "e";
          else if (str == "f") s = "f";
          else if (str == "g") s = "g";
          else if (str == "h") s = "h";
          else if (str == "i") s = "i";
          else if (str == "j") s = "j";
          else if (str == "k") s = "k";
          else if (str == "l") s = "l";
          else if (str == "m") s = "m";
          else if (str == "n") s = "n";
          else if (str == "o") s = "o";
          else if (str == "p") s = "p";
          else if (str == "q") s = "q";
          else if (str == "r") s = "r";
          else if (str == "s") s = "s";
          else if (str == "t") s = "t";
          else if (str == "u") s = "u";
          else if (str == "v") s = "v";
          else if (str == "w") s = "w";
          else if (str == "x") s = "x";
          else if (str == "y") s = "y";
          else if (str == "z") s = "z";
        });

    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("5 unique letters - switch", [&] {
          switch (str[0]) {
            break; case 'a': s = "a";
            break; case 'b': s = "b";
            break; case 'c': s = "c";
            break; case 'd': s = "d";
            break; case 'e': s = "e";
            break; case 'f': s = "f";
            break; case 'g': s = "g";
            break; case 'h': s = "h";
            break; case 'i': s = "i";
            break; case 'j': s = "j";
            break; case 'k': s = "k";
            break; case 'l': s = "l";
            break; case 'm': s = "m";
            break; case 'n': s = "n";
            break; case 'o': s = "o";
            break; case 'p': s = "p";
            break; case 'q': s = "q";
            break; case 'r': s = "r";
            break; case 's': s = "s";
            break; case 't': s = "t";
            break; case 'u': s = "u";
            break; case 'v': s = "v";
            break; case 'w': s = "w";
            break; case 'x': s = "x";
            break; case 'y': s = "y";
            break; case 'z': s = "z";
            break; case 'a': s = "a";
            break; case 'b': s = "b";
            break; case 'c': s = "c";
            break; case 'd': s = "d";
            break; case 'e': s = "e";
            break; case 'f': s = "f";
            break; case 'g': s = "g";
            break; case 'h': s = "h";
            break; case 'i': s = "i";
            break; case 'j': s = "j";
            break; case 'k': s = "k";
            break; case 'l': s = "l";
            break; case 'm': s = "m";
            break; case 'n': s = "n";
            break; case 'o': s = "o";
            break; case 'p': s = "p";
            break; case 'q': s = "q";
            break; case 'r': s = "r";
            break; case 's': s = "s";
            break; case 't': s = "t";
            break; case 'u': s = "u";
            break; case 'v': s = "v";
            break; case 'w': s = "w";
            break; case 'x': s = "x";
            break; case 'y': s = "y";
            break; case 'z': s = "z";
          }
        });
}


auto words_26_characters_1()
{
    std::string str = "z";
    std::string s;
    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("5 unique letters - match", [&] {
          s = match(str) return "";
          case("a") return "a";
          case("b") return "b";
          case("c") return "c";
          case("d") return "d";
          case("e") return "e";
          case("f") return "f";
          case("g") return "g";
          case("h") return "h";
          case("i") return "i";
          case("j") return "j";
          case("k") return "k";
          case("l") return "l";
          case("m") return "m";
          case("n") return "n";
          case("o") return "o";
          case("p") return "p";
          case("q") return "q";
          case("r") return "r";
          case("s") return "s";
          case("t") return "t";
          case("u") return "u";
          case("v") return "v";
          case("w") return "w";
          case("x") return "x";
          case("y") return "y";
          case("z") return "z";
          endmatch;
        });

    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("5 unique letters - if", [&] {
          if (str == "a") s = "a";
          else if (str == "b") s = "b";
          else if (str == "c") s = "c";
          else if (str == "d") s = "d";
          else if (str == "e") s = "e";
          else if (str == "f") s = "f";
          else if (str == "g") s = "g";
          else if (str == "h") s = "h";
          else if (str == "i") s = "i";
          else if (str == "j") s = "j";
          else if (str == "k") s = "k";
          else if (str == "l") s = "l";
          else if (str == "m") s = "m";
          else if (str == "n") s = "n";
          else if (str == "o") s = "o";
          else if (str == "p") s = "p";
          else if (str == "q") s = "q";
          else if (str == "r") s = "r";
          else if (str == "s") s = "s";
          else if (str == "t") s = "t";
          else if (str == "u") s = "u";
          else if (str == "v") s = "v";
          else if (str == "w") s = "w";
          else if (str == "x") s = "x";
          else if (str == "y") s = "y";
          else if (str == "z") s = "z";
        });

    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("5 unique letters - switch", [&] {
          switch (str[0]) {
            break; case 'a': s = "a";
            break; case 'b': s = "b";
            break; case 'c': s = "c";
            break; case 'd': s = "d";
            break; case 'e': s = "e";
            break; case 'f': s = "f";
            break; case 'g': s = "g";
            break; case 'h': s = "h";
            break; case 'i': s = "i";
            break; case 'j': s = "j";
            break; case 'k': s = "k";
            break; case 'l': s = "l";
            break; case 'm': s = "m";
            break; case 'n': s = "n";
            break; case 'o': s = "o";
            break; case 'p': s = "p";
            break; case 'q': s = "q";
            break; case 'r': s = "r";
            break; case 's': s = "s";
            break; case 't': s = "t";
            break; case 'u': s = "u";
            break; case 'v': s = "v";
            break; case 'w': s = "w";
            break; case 'x': s = "x";
            break; case 'y': s = "y";
            break; case 'z': s = "z";
          }
        });
}

auto words_26_characters_2()
{
    /*
     * 5 unique letters
     */
    std::string str = "zz";
    std::string s;
    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("2 letters - match", [&] {
          s = match(str) return "";
          case("aa") return "aa";
          case("bb") return "bb";
          case("cc") return "cc";
          case("dd") return "dd";
          case("ee") return "ee";
          case("ff") return "ff";
          case("gg") return "gg";
          case("hh") return "hh";
          case("ii") return "ii";
          case("jj") return "jj";
          case("kk") return "kk";
          case("ll") return "ll";
          case("mm") return "mm";
          case("nn") return "nn";
          case("oo") return "oo";
          case("pp") return "pp";
          case("qq") return "qq";
          case("rr") return "rr";
          case("ss") return "ss";
          case("tt") return "tt";
          case("uu") return "uu";
          case("vv") return "vv";
          case("ww") return "ww";
          case("xx") return "xx";
          case("yy") return "yy";
          case("zz") return "zz";
          endmatch;
        });

    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("2 letters - if", [&] {
          if (str == "aa") s = "aa";
          else if (str == "bb") s = "bb";
          else if (str == "cc") s = "cc";
          else if (str == "dd") s = "dd";
          else if (str == "ee") s = "ee";
          else if (str == "ff") s = "ff";
          else if (str == "gg") s = "gg";
          else if (str == "hh") s = "hh";
          else if (str == "ii") s = "ii";
          else if (str == "jj") s = "jj";
          else if (str == "kk") s = "kk";
          else if (str == "ll") s = "ll";
          else if (str == "mm") s = "mm";
          else if (str == "nn") s = "nn";
          else if (str == "oo") s = "oo";
          else if (str == "pp") s = "pp";
          else if (str == "qq") s = "qq";
          else if (str == "rr") s = "rr";
          else if (str == "ss") s = "ss";
          else if (str == "tt") s = "tt";
          else if (str == "uu") s = "uu";
          else if (str == "vv") s = "vv";
          else if (str == "ww") s = "ww";
          else if (str == "xx") s = "xx";
          else if (str == "yy") s = "yy";
          else if (str == "zz") s = "zz";
        });

    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("2 letters - switch", [&] {
          switch (str[0]) {
            break; case 'a': switch(str[1]) { break; case 'a' : s = "aa"; }
            break; case 'b': switch(str[1]) { break; case 'b' : s = "bb"; }
            break; case 'c': switch(str[1]) { break; case 'c' : s = "cc"; }
            break; case 'd': switch(str[1]) { break; case 'd' : s = "dd"; }
            break; case 'e': switch(str[1]) { break; case 'e' : s = "ee"; }
            break; case 'f': switch(str[1]) { break; case 'f' : s = "ff"; }
            break; case 'g': switch(str[1]) { break; case 'g' : s = "gg"; }
            break; case 'h': switch(str[1]) { break; case 'h' : s = "hh"; }
            break; case 'i': switch(str[1]) { break; case 'i' : s = "ii"; }
            break; case 'j': switch(str[1]) { break; case 'j' : s = "jj"; }
            break; case 'k': switch(str[1]) { break; case 'k' : s = "kk"; }
            break; case 'l': switch(str[1]) { break; case 'l' : s = "ll"; }
            break; case 'm': switch(str[1]) { break; case 'm' : s = "mm"; }
            break; case 'n': switch(str[1]) { break; case 'n' : s = "nn"; }
            break; case 'o': switch(str[1]) { break; case 'o' : s = "oo"; }
            break; case 'p': switch(str[1]) { break; case 'p' : s = "pp"; }
            break; case 'q': switch(str[1]) { break; case 'q' : s = "qq"; }
            break; case 'r': switch(str[1]) { break; case 'r' : s = "rr"; }
            break; case 's': switch(str[1]) { break; case 's' : s = "ss"; }
            break; case 't': switch(str[1]) { break; case 't' : s = "tt"; }
            break; case 'u': switch(str[1]) { break; case 'u' : s = "uu"; }
            break; case 'v': switch(str[1]) { break; case 'v' : s = "vv"; }
            break; case 'w': switch(str[1]) { break; case 'w' : s = "ww"; }
            break; case 'x': switch(str[1]) { break; case 'x' : s = "xx"; }
            break; case 'y': switch(str[1]) { break; case 'y' : s = "yy"; }
            break; case 'z': switch(str[1]) { break; case 'z' : s = "zz"; }
          }
        });
}

auto words_26_characters_3()
{
    /*
     * 5 unique letters
     */
    std::string str = "zzz";
    std::string s;
    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("3 letters - match", [&] {
          s = match(str) return "";
          case("aaa") return "aaa";
          case("bbb") return "bbb";
          case("ccc") return "ccc";
          case("ddd") return "ddd";
          case("eee") return "eee";
          case("fff") return "fff";
          case("ggg") return "ggg";
          case("hhh") return "hhh";
          case("iii") return "iii";
          case("jjj") return "jjj";
          case("kkk") return "kkk";
          case("lll") return "lll";
          case("mmm") return "mmm";
          case("nnn") return "nnn";
          case("ooo") return "ooo";
          case("ppp") return "ppp";
          case("qqq") return "qqq";
          case("rrr") return "rrr";
          case("sss") return "sss";
          case("ttt") return "ttt";
          case("uuu") return "uuu";
          case("vvv") return "vvv";
          case("www") return "www";
          case("xxx") return "xxx";
          case("yyy") return "yyy";
          case("zzz") return "zzz";
          endmatch;
        });

    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("3 letters - if", [&] {
          if (str == "aaa") s = "aaa";
          else if (str == "bbb") s = "bbb";
          else if (str == "ccc") s = "ccc";
          else if (str == "ddd") s = "ddd";
          else if (str == "eee") s = "eee";
          else if (str == "fff") s = "fff";
          else if (str == "ggg") s = "ggg";
          else if (str == "hhh") s = "hhh";
          else if (str == "iii") s = "iii";
          else if (str == "jjj") s = "jjj";
          else if (str == "kkk") s = "kkk";
          else if (str == "lll") s = "lll";
          else if (str == "mmm") s = "mmm";
          else if (str == "nnn") s = "nnn";
          else if (str == "ooo") s = "ooo";
          else if (str == "ppp") s = "ppp";
          else if (str == "qqq") s = "qqq";
          else if (str == "rrr") s = "rrr";
          else if (str == "sss") s = "sss";
          else if (str == "ttt") s = "ttt";
          else if (str == "uuu") s = "uuu";
          else if (str == "vvv") s = "vvv";
          else if (str == "www") s = "www";
          else if (str == "xxx") s = "xxx";
          else if (str == "yyy") s = "yyy";
          else if (str == "zzz") s = "zzz";
        });

    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("3 letters - switch", [&] {
          switch (str[0]) {
            break; case 'a': switch(str[1]) { break; case 'a' : switch(str[2]) { break; case 'a' : s = "aaa"; } }
            break; case 'b': switch(str[1]) { break; case 'b' : switch(str[2]) { break; case 'b' : s = "bbb"; } }
            break; case 'c': switch(str[1]) { break; case 'c' : switch(str[2]) { break; case 'c' : s = "ccc"; } }
            break; case 'd': switch(str[1]) { break; case 'd' : switch(str[2]) { break; case 'd' : s = "ddd"; } }
            break; case 'e': switch(str[1]) { break; case 'e' : switch(str[2]) { break; case 'e' : s = "eee"; } }
            break; case 'f': switch(str[1]) { break; case 'f' : switch(str[2]) { break; case 'f' : s = "fff"; } }
            break; case 'g': switch(str[1]) { break; case 'g' : switch(str[2]) { break; case 'g' : s = "ggg"; } }
            break; case 'h': switch(str[1]) { break; case 'h' : switch(str[2]) { break; case 'h' : s = "hhh"; } }
            break; case 'i': switch(str[1]) { break; case 'i' : switch(str[2]) { break; case 'i' : s = "iii"; } }
            break; case 'j': switch(str[1]) { break; case 'j' : switch(str[2]) { break; case 'j' : s = "jjj"; } }
            break; case 'k': switch(str[1]) { break; case 'k' : switch(str[2]) { break; case 'k' : s = "kkk"; } }
            break; case 'l': switch(str[1]) { break; case 'l' : switch(str[2]) { break; case 'l' : s = "lll"; } }
            break; case 'm': switch(str[1]) { break; case 'm' : switch(str[2]) { break; case 'm' : s = "mmm"; } }
            break; case 'n': switch(str[1]) { break; case 'n' : switch(str[2]) { break; case 'n' : s = "nnn"; } }
            break; case 'o': switch(str[1]) { break; case 'o' : switch(str[2]) { break; case 'o' : s = "ooo"; } }
            break; case 'p': switch(str[1]) { break; case 'p' : switch(str[2]) { break; case 'p' : s = "ppp"; } }
            break; case 'q': switch(str[1]) { break; case 'q' : switch(str[2]) { break; case 'q' : s = "qqq"; } }
            break; case 'r': switch(str[1]) { break; case 'r' : switch(str[2]) { break; case 'r' : s = "rrr"; } }
            break; case 's': switch(str[1]) { break; case 's' : switch(str[2]) { break; case 's' : s = "sss"; } }
            break; case 't': switch(str[1]) { break; case 't' : switch(str[2]) { break; case 't' : s = "ttt"; } }
            break; case 'u': switch(str[1]) { break; case 'u' : switch(str[2]) { break; case 'u' : s = "uuu"; } }
            break; case 'v': switch(str[1]) { break; case 'v' : switch(str[2]) { break; case 'v' : s = "vvv"; } }
            break; case 'w': switch(str[1]) { break; case 'w' : switch(str[2]) { break; case 'w' : s = "www"; } }
            break; case 'x': switch(str[1]) { break; case 'x' : switch(str[2]) { break; case 'x' : s = "xxx"; } }
            break; case 'y': switch(str[1]) { break; case 'y' : switch(str[2]) { break; case 'y' : s = "yyy"; } }
            break; case 'z': switch(str[1]) { break; case 'z' : switch(str[2]) { break; case 'z' : s = "zzz"; } }
          }
        });
}

auto words_26_characters_4()
{
    /*
     * 5 unique letters
     */
    std::string str = "zzzz";
    std::string s;
    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("4 letters - match", [&] {
          s = match(str) return "";
          case("aaaa") return "aaaa";
          case("bbbb") return "bbbb";
          case("cccc") return "cccc";
          case("dddd") return "dddd";
          case("eeee") return "eeee";
          case("ffff") return "ffff";
          case("gggg") return "gggg";
          case("hhhh") return "hhhh";
          case("iiii") return "iiii";
          case("jjjj") return "jjjj";
          case("kkkk") return "kkkk";
          case("llll") return "llll";
          case("mmmm") return "mmmm";
          case("nnnn") return "nnnn";
          case("oooo") return "oooo";
          case("pppp") return "pppp";
          case("qqqq") return "qqqq";
          case("rrrr") return "rrrr";
          case("ssss") return "ssss";
          case("tttt") return "tttt";
          case("uuuu") return "uuuu";
          case("vvvv") return "vvvv";
          case("wwww") return "wwww";
          case("xxxx") return "xxxx";
          case("yyyy") return "yyyy";
          case("zzzz") return "zzzz";
          endmatch;
        });

    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("4 letters - if", [&] {
          if (str == "aaaa") s = "aaaa";
          else if (str == "bbbb") s = "bbbb";
          else if (str == "cccc") s = "cccc";
          else if (str == "dddd") s = "dddd";
          else if (str == "eeee") s = "eeee";
          else if (str == "ffff") s = "ffff";
          else if (str == "gggg") s = "gggg";
          else if (str == "hhhh") s = "hhhh";
          else if (str == "iiii") s = "iiii";
          else if (str == "jjjj") s = "jjjj";
          else if (str == "kkkk") s = "kkkk";
          else if (str == "llll") s = "llll";
          else if (str == "mmmm") s = "mmmm";
          else if (str == "nnnn") s = "nnnn";
          else if (str == "oooo") s = "oooo";
          else if (str == "pppp") s = "pppp";
          else if (str == "qqqq") s = "qqqq";
          else if (str == "rrrr") s = "rrrr";
          else if (str == "ssss") s = "ssss";
          else if (str == "tttt") s = "tttt";
          else if (str == "uuuu") s = "uuuu";
          else if (str == "vvvv") s = "vvvv";
          else if (str == "wwww") s = "wwww";
          else if (str == "xxxx") s = "xxxx";
          else if (str == "yyyy") s = "yyyy";
          else if (str == "zzzz") s = "zzzz";
        });

    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("4 letters - switch", [&] {
          switch (str[0]) {
            break; case 'a': switch(str[1]) { break; case 'a' : switch(str[2]) { break; case 'a' : switch(str[3]) { break; case 'a' : s = "aaaa"; } } } 
            break; case 'b': switch(str[1]) { break; case 'b' : switch(str[2]) { break; case 'b' : switch(str[3]) { break; case 'b' : s = "bbbb"; } } } 
            break; case 'c': switch(str[1]) { break; case 'c' : switch(str[2]) { break; case 'c' : switch(str[3]) { break; case 'c' : s = "cccc"; } } } 
            break; case 'd': switch(str[1]) { break; case 'd' : switch(str[2]) { break; case 'd' : switch(str[3]) { break; case 'd' : s = "dddd"; } } } 
            break; case 'e': switch(str[1]) { break; case 'e' : switch(str[2]) { break; case 'e' : switch(str[3]) { break; case 'e' : s = "eeee"; } } } 
            break; case 'f': switch(str[1]) { break; case 'f' : switch(str[2]) { break; case 'f' : switch(str[3]) { break; case 'f' : s = "ffff"; } } } 
            break; case 'g': switch(str[1]) { break; case 'g' : switch(str[2]) { break; case 'g' : switch(str[3]) { break; case 'g' : s = "gggg"; } } } 
            break; case 'h': switch(str[1]) { break; case 'h' : switch(str[2]) { break; case 'h' : switch(str[3]) { break; case 'h' : s = "hhhh"; } } } 
            break; case 'i': switch(str[1]) { break; case 'i' : switch(str[2]) { break; case 'i' : switch(str[3]) { break; case 'i' : s = "iiii"; } } } 
            break; case 'j': switch(str[1]) { break; case 'j' : switch(str[2]) { break; case 'j' : switch(str[3]) { break; case 'j' : s = "jjjj"; } } } 
            break; case 'k': switch(str[1]) { break; case 'k' : switch(str[2]) { break; case 'k' : switch(str[3]) { break; case 'k' : s = "kkkk"; } } } 
            break; case 'l': switch(str[1]) { break; case 'l' : switch(str[2]) { break; case 'l' : switch(str[3]) { break; case 'l' : s = "llll"; } } } 
            break; case 'm': switch(str[1]) { break; case 'm' : switch(str[2]) { break; case 'm' : switch(str[3]) { break; case 'm' : s = "mmmm"; } } } 
            break; case 'n': switch(str[1]) { break; case 'n' : switch(str[2]) { break; case 'n' : switch(str[3]) { break; case 'n' : s = "nnnn"; } } } 
            break; case 'o': switch(str[1]) { break; case 'o' : switch(str[2]) { break; case 'o' : switch(str[3]) { break; case 'o' : s = "oooo"; } } } 
            break; case 'p': switch(str[1]) { break; case 'p' : switch(str[2]) { break; case 'p' : switch(str[3]) { break; case 'p' : s = "pppp"; } } } 
            break; case 'q': switch(str[1]) { break; case 'q' : switch(str[2]) { break; case 'q' : switch(str[3]) { break; case 'q' : s = "qqqq"; } } } 
            break; case 'r': switch(str[1]) { break; case 'r' : switch(str[2]) { break; case 'r' : switch(str[3]) { break; case 'r' : s = "rrrr"; } } } 
            break; case 's': switch(str[1]) { break; case 's' : switch(str[2]) { break; case 's' : switch(str[3]) { break; case 's' : s = "ssss"; } } } 
            break; case 't': switch(str[1]) { break; case 't' : switch(str[2]) { break; case 't' : switch(str[3]) { break; case 't' : s = "tttt"; } } } 
            break; case 'u': switch(str[1]) { break; case 'u' : switch(str[2]) { break; case 'u' : switch(str[3]) { break; case 'u' : s = "uuuu"; } } } 
            break; case 'v': switch(str[1]) { break; case 'v' : switch(str[2]) { break; case 'v' : switch(str[3]) { break; case 'v' : s = "vvvv"; } } } 
            break; case 'w': switch(str[1]) { break; case 'w' : switch(str[2]) { break; case 'w' : switch(str[3]) { break; case 'w' : s = "wwww"; } } } 
            break; case 'x': switch(str[1]) { break; case 'x' : switch(str[2]) { break; case 'x' : switch(str[3]) { break; case 'x' : s = "xxxx"; } } } 
            break; case 'y': switch(str[1]) { break; case 'y' : switch(str[2]) { break; case 'y' : switch(str[3]) { break; case 'y' : s = "yyyy"; } } } 
            break; case 'z': switch(str[1]) { break; case 'z' : switch(str[2]) { break; case 'z' : switch(str[3]) { break; case 'z' : s = "zzzz"; } } } 
          }
        });
}

auto words_26_characters_5()
{
    std::string str = "zzzzz";
    std::string s1;
    std::string s2;
    std::string s3;
    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("5 letters - match", [&] {
          s1 = match(str) return "";
          case("aaaaa") return "aaaaa";
          case("bbbbb") return "bbbbb";
          case("ccccc") return "ccccc";
          case("ddddd") return "ddddd";
          case("eeeee") return "eeeee";
          case("fffff") return "fffff";
          case("ggggg") return "ggggg";
          case("hhhhh") return "hhhhh";
          case("iiiii") return "iiiii";
          case("jjjjj") return "jjjjj";
          case("kkkkk") return "kkkkk";
          case("lllll") return "lllll";
          case("mmmmm") return "mmmmm";
          case("nnnnn") return "nnnnn";
          case("ooooo") return "ooooo";
          case("ppppp") return "ppppp";
          case("qqqqq") return "qqqqq";
          case("rrrrr") return "rrrrr";
          case("sssss") return "sssss";
          case("ttttt") return "ttttt";
          case("uuuuu") return "uuuuu";
          case("vvvvv") return "vvvvv";
          case("wwwww") return "wwwww";
          case("xxxxx") return "xxxxx";
          case("yyyyy") return "yyyyy";
          case("zzzzz") return "zzzzz";
          endmatch;
        });

    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("5 letters - if", [&] {
          if (str == "aaaaa") s2 = "aaaaa";
          else if (str == "bbbbb") s2 = "bbbbb";
          else if (str == "ccccc") s2 = "ccccc";
          else if (str == "ddddd") s2 = "ddddd";
          else if (str == "eeeee") s2 = "eeeee";
          else if (str == "fffff") s2 = "fffff";
          else if (str == "ggggg") s2 = "ggggg";
          else if (str == "hhhhh") s2 = "hhhhh";
          else if (str == "iiiii") s2 = "iiiii";
          else if (str == "jjjjj") s2 = "jjjjj";
          else if (str == "kkkkk") s2 = "kkkkk";
          else if (str == "lllll") s2 = "lllll";
          else if (str == "mmmmm") s2 = "mmmmm";
          else if (str == "nnnnn") s2 = "nnnnn";
          else if (str == "ooooo") s2 = "ooooo";
          else if (str == "ppppp") s2 = "ppppp";
          else if (str == "qqqqq") s2 = "qqqqq";
          else if (str == "rrrrr") s2 = "rrrrr";
          else if (str == "sssss") s2 = "sssss";
          else if (str == "ttttt") s2 = "ttttt";
          else if (str == "uuuuu") s2 = "uuuuu";
          else if (str == "vvvvv") s2 = "vvvvv";
          else if (str == "wwwww") s2 = "wwwww";
          else if (str == "xxxxx") s2 = "xxxxx";
          else if (str == "yyyyy") s2 = "yyyyy";
          else if (str == "zzzzz") s2 = "zzzzz";
        });

    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("5 letters - switch", [&] {
          switch (str[0]) {
            break; case 'a': switch(str[1]) { break; case 'a' : switch(str[2]) { break; case 'a' : switch(str[3]) { break; case 'a' : switch(str[4]) { break; case 'a' : s3 = "aaaaa"; } } } } 
            break; case 'b': switch(str[1]) { break; case 'b' : switch(str[2]) { break; case 'b' : switch(str[3]) { break; case 'b' : switch(str[4]) { break; case 'b' : s3 = "bbbbb"; } } } } 
            break; case 'c': switch(str[1]) { break; case 'c' : switch(str[2]) { break; case 'c' : switch(str[3]) { break; case 'c' : switch(str[4]) { break; case 'c' : s3 = "ccccc"; } } } } 
            break; case 'd': switch(str[1]) { break; case 'd' : switch(str[2]) { break; case 'd' : switch(str[3]) { break; case 'd' : switch(str[4]) { break; case 'd' : s3 = "ddddd"; } } } } 
            break; case 'e': switch(str[1]) { break; case 'e' : switch(str[2]) { break; case 'e' : switch(str[3]) { break; case 'e' : switch(str[4]) { break; case 'e' : s3 = "eeeee"; } } } } 
            break; case 'f': switch(str[1]) { break; case 'f' : switch(str[2]) { break; case 'f' : switch(str[3]) { break; case 'f' : switch(str[4]) { break; case 'f' : s3 = "fffff"; } } } } 
            break; case 'g': switch(str[1]) { break; case 'g' : switch(str[2]) { break; case 'g' : switch(str[3]) { break; case 'g' : switch(str[4]) { break; case 'g' : s3 = "ggggg"; } } } } 
            break; case 'h': switch(str[1]) { break; case 'h' : switch(str[2]) { break; case 'h' : switch(str[3]) { break; case 'h' : switch(str[4]) { break; case 'h' : s3 = "hhhhh"; } } } } 
            break; case 'i': switch(str[1]) { break; case 'i' : switch(str[2]) { break; case 'i' : switch(str[3]) { break; case 'i' : switch(str[4]) { break; case 'i' : s3 = "iiiii"; } } } } 
            break; case 'j': switch(str[1]) { break; case 'j' : switch(str[2]) { break; case 'j' : switch(str[3]) { break; case 'j' : switch(str[4]) { break; case 'j' : s3 = "jjjjj"; } } } } 
            break; case 'k': switch(str[1]) { break; case 'k' : switch(str[2]) { break; case 'k' : switch(str[3]) { break; case 'k' : switch(str[4]) { break; case 'k' : s3 = "kkkkk"; } } } } 
            break; case 'l': switch(str[1]) { break; case 'l' : switch(str[2]) { break; case 'l' : switch(str[3]) { break; case 'l' : switch(str[4]) { break; case 'l' : s3 = "lllll"; } } } } 
            break; case 'm': switch(str[1]) { break; case 'm' : switch(str[2]) { break; case 'm' : switch(str[3]) { break; case 'm' : switch(str[4]) { break; case 'm' : s3 = "mmmmm"; } } } } 
            break; case 'n': switch(str[1]) { break; case 'n' : switch(str[2]) { break; case 'n' : switch(str[3]) { break; case 'n' : switch(str[4]) { break; case 'n' : s3 = "nnnnn"; } } } } 
            break; case 'o': switch(str[1]) { break; case 'o' : switch(str[2]) { break; case 'o' : switch(str[3]) { break; case 'o' : switch(str[4]) { break; case 'o' : s3 = "ooooo"; } } } } 
            break; case 'p': switch(str[1]) { break; case 'p' : switch(str[2]) { break; case 'p' : switch(str[3]) { break; case 'p' : switch(str[4]) { break; case 'p' : s3 = "ppppp"; } } } } 
            break; case 'q': switch(str[1]) { break; case 'q' : switch(str[2]) { break; case 'q' : switch(str[3]) { break; case 'q' : switch(str[4]) { break; case 'q' : s3 = "qqqqq"; } } } } 
            break; case 'r': switch(str[1]) { break; case 'r' : switch(str[2]) { break; case 'r' : switch(str[3]) { break; case 'r' : switch(str[4]) { break; case 'r' : s3 = "rrrrr"; } } } } 
            break; case 's': switch(str[1]) { break; case 's' : switch(str[2]) { break; case 's' : switch(str[3]) { break; case 's' : switch(str[4]) { break; case 's' : s3 = "sssss"; } } } } 
            break; case 't': switch(str[1]) { break; case 't' : switch(str[2]) { break; case 't' : switch(str[3]) { break; case 't' : switch(str[4]) { break; case 't' : s3 = "ttttt"; } } } } 
            break; case 'u': switch(str[1]) { break; case 'u' : switch(str[2]) { break; case 'u' : switch(str[3]) { break; case 'u' : switch(str[4]) { break; case 'u' : s3 = "uuuuu"; } } } } 
            break; case 'v': switch(str[1]) { break; case 'v' : switch(str[2]) { break; case 'v' : switch(str[3]) { break; case 'v' : switch(str[4]) { break; case 'v' : s3 = "vvvvv"; } } } } 
            break; case 'w': switch(str[1]) { break; case 'w' : switch(str[2]) { break; case 'w' : switch(str[3]) { break; case 'w' : switch(str[4]) { break; case 'w' : s3 = "wwwww"; } } } } 
            break; case 'x': switch(str[1]) { break; case 'x' : switch(str[2]) { break; case 'x' : switch(str[3]) { break; case 'x' : switch(str[4]) { break; case 'x' : s3 = "xxxxx"; } } } } 
            break; case 'y': switch(str[1]) { break; case 'y' : switch(str[2]) { break; case 'y' : switch(str[3]) { break; case 'y' : switch(str[4]) { break; case 'y' : s3 = "yyyyy"; } } } } 
            break; case 'z': switch(str[1]) { break; case 'z' : switch(str[2]) { break; case 'z' : switch(str[3]) { break; case 'z' : switch(str[4]) { break; case 'z' : s3 = "zzzzz"; } } } } 
          }
        });
}


auto words_52_characters_5()
{
    std::string str = "zzzzz";
    std::string s1;
    std::string s2;
    std::string s3;
    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("5 letters - match", [&] {
          s1 = match(str) return "";
          case("aaaaa") return "aaaaa";
          case("bbbbb") return "bbbbb";
          case("ccccc") return "ccccc";
          case("ddddd") return "ddddd";
          case("eeeee") return "eeeee";
          case("fffff") return "fffff";
          case("ggggg") return "ggggg";
          case("hhhhh") return "hhhhh";
          case("iiiii") return "iiiii";
          case("jjjjj") return "jjjjj";
          case("kkkkk") return "kkkkk";
          case("lllll") return "lllll";
          case("mmmmm") return "mmmmm";
          case("nnnnn") return "nnnnn";
          case("ooooo") return "ooooo";
          case("ppppp") return "ppppp";
          case("qqqqq") return "qqqqq";
          case("rrrrr") return "rrrrr";
          case("sssss") return "sssss";
          case("ttttt") return "ttttt";
          case("uuuuu") return "uuuuu";
          case("vvvvv") return "vvvvv";
          case("wwwww") return "wwwww";
          case("xxxxx") return "xxxxx";
          case("yyyyy") return "yyyyy";
          case("zzzzz") return "zzzzz";
          case("aaaaa") return "aaaaa";
          case("bbbbb") return "bbbbb";
          case("ccccc") return "ccccc";
          case("ddddd") return "ddddd";
          case("eeeee") return "eeeee";
          case("fffff") return "fffff";
          case("ggggg") return "ggggg";
          case("hhhhh") return "hhhhh";
          case("iiiii") return "iiiii";
          case("jjjjj") return "jjjjj";
          case("kkkkk") return "kkkkk";
          case("lllll") return "lllll";
          case("mmmmm") return "mmmmm";
          case("nnnnn") return "nnnnn";
          case("ooooo") return "ooooo";
          case("ppppp") return "ppppp";
          case("qqqqq") return "qqqqq";
          case("rrrrr") return "rrrrr";
          case("sssss") return "sssss";
          case("ttttt") return "ttttt";
          case("uuuuu") return "uuuuu";
          case("vvvvv") return "vvvvv";
          case("wwwww") return "wwwww";
          case("xxxxx") return "xxxxx";
          case("yyyyy") return "yyyyy";
          case("zzzzz") return "zzzzz";
          endmatch;
        });

    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("5 letters - if", [&] {
          if (str == "aaaaa") s2 = "aaaaa";
          else if (str == "bbbbb") s2 = "bbbbb";
          else if (str == "ccccc") s2 = "ccccc";
          else if (str == "ddddd") s2 = "ddddd";
          else if (str == "eeeee") s2 = "eeeee";
          else if (str == "fffff") s2 = "fffff";
          else if (str == "ggggg") s2 = "ggggg";
          else if (str == "hhhhh") s2 = "hhhhh";
          else if (str == "iiiii") s2 = "iiiii";
          else if (str == "jjjjj") s2 = "jjjjj";
          else if (str == "kkkkk") s2 = "kkkkk";
          else if (str == "lllll") s2 = "lllll";
          else if (str == "mmmmm") s2 = "mmmmm";
          else if (str == "nnnnn") s2 = "nnnnn";
          else if (str == "ooooo") s2 = "ooooo";
          else if (str == "ppppp") s2 = "ppppp";
          else if (str == "qqqqq") s2 = "qqqqq";
          else if (str == "rrrrr") s2 = "rrrrr";
          else if (str == "sssss") s2 = "sssss";
          else if (str == "ttttt") s2 = "ttttt";
          else if (str == "uuuuu") s2 = "uuuuu";
          else if (str == "vvvvv") s2 = "vvvvv";
          else if (str == "wwwww") s2 = "wwwww";
          else if (str == "xxxxx") s2 = "xxxxx";
          else if (str == "yyyyy") s2 = "yyyyy";
          else if (str == "zzzzz") s2 = "zzzzz";
          else if (str == "aaaaa") s2 = "aaaaa";
          else if (str == "bbbbb") s2 = "bbbbb";
          else if (str == "ccccc") s2 = "ccccc";
          else if (str == "ddddd") s2 = "ddddd";
          else if (str == "eeeee") s2 = "eeeee";
          else if (str == "fffff") s2 = "fffff";
          else if (str == "ggggg") s2 = "ggggg";
          else if (str == "hhhhh") s2 = "hhhhh";
          else if (str == "iiiii") s2 = "iiiii";
          else if (str == "jjjjj") s2 = "jjjjj";
          else if (str == "kkkkk") s2 = "kkkkk";
          else if (str == "lllll") s2 = "lllll";
          else if (str == "mmmmm") s2 = "mmmmm";
          else if (str == "nnnnn") s2 = "nnnnn";
          else if (str == "ooooo") s2 = "ooooo";
          else if (str == "ppppp") s2 = "ppppp";
          else if (str == "qqqqq") s2 = "qqqqq";
          else if (str == "rrrrr") s2 = "rrrrr";
          else if (str == "sssss") s2 = "sssss";
          else if (str == "ttttt") s2 = "ttttt";
          else if (str == "uuuuu") s2 = "uuuuu";
          else if (str == "vvvvv") s2 = "vvvvv";
          else if (str == "wwwww") s2 = "wwwww";
          else if (str == "xxxxx") s2 = "xxxxx";
          else if (str == "yyyyy") s2 = "yyyyy";
          else if (str == "zzzzz") s2 = "zzzzz";
        });

    ankerl::nanobench::bench()
        .epochs(epochs)
        .minepochiterations(epoch_iterations)
        .run("5 letters - switch", [&] {
          switch (str[0]) {
            break; case 'a': switch(str[1]) { break; case 'a' : switch(str[2]) { break; case 'a' : switch(str[3]) { break; case 'a' : switch(str[4]) { break; case 'a' : s3 = "aaaaa"; } } } } 
            break; case 'b': switch(str[1]) { break; case 'b' : switch(str[2]) { break; case 'b' : switch(str[3]) { break; case 'b' : switch(str[4]) { break; case 'b' : s3 = "bbbbb"; } } } } 
            break; case 'c': switch(str[1]) { break; case 'c' : switch(str[2]) { break; case 'c' : switch(str[3]) { break; case 'c' : switch(str[4]) { break; case 'c' : s3 = "ccccc"; } } } } 
            break; case 'd': switch(str[1]) { break; case 'd' : switch(str[2]) { break; case 'd' : switch(str[3]) { break; case 'd' : switch(str[4]) { break; case 'd' : s3 = "ddddd"; } } } } 
            break; case 'e': switch(str[1]) { break; case 'e' : switch(str[2]) { break; case 'e' : switch(str[3]) { break; case 'e' : switch(str[4]) { break; case 'e' : s3 = "eeeee"; } } } } 
            break; case 'f': switch(str[1]) { break; case 'f' : switch(str[2]) { break; case 'f' : switch(str[3]) { break; case 'f' : switch(str[4]) { break; case 'f' : s3 = "fffff"; } } } } 
            break; case 'g': switch(str[1]) { break; case 'g' : switch(str[2]) { break; case 'g' : switch(str[3]) { break; case 'g' : switch(str[4]) { break; case 'g' : s3 = "ggggg"; } } } } 
            break; case 'h': switch(str[1]) { break; case 'h' : switch(str[2]) { break; case 'h' : switch(str[3]) { break; case 'h' : switch(str[4]) { break; case 'h' : s3 = "hhhhh"; } } } } 
            break; case 'i': switch(str[1]) { break; case 'i' : switch(str[2]) { break; case 'i' : switch(str[3]) { break; case 'i' : switch(str[4]) { break; case 'i' : s3 = "iiiii"; } } } } 
            break; case 'j': switch(str[1]) { break; case 'j' : switch(str[2]) { break; case 'j' : switch(str[3]) { break; case 'j' : switch(str[4]) { break; case 'j' : s3 = "jjjjj"; } } } } 
            break; case 'k': switch(str[1]) { break; case 'k' : switch(str[2]) { break; case 'k' : switch(str[3]) { break; case 'k' : switch(str[4]) { break; case 'k' : s3 = "kkkkk"; } } } } 
            break; case 'l': switch(str[1]) { break; case 'l' : switch(str[2]) { break; case 'l' : switch(str[3]) { break; case 'l' : switch(str[4]) { break; case 'l' : s3 = "lllll"; } } } } 
            break; case 'm': switch(str[1]) { break; case 'm' : switch(str[2]) { break; case 'm' : switch(str[3]) { break; case 'm' : switch(str[4]) { break; case 'm' : s3 = "mmmmm"; } } } } 
            break; case 'n': switch(str[1]) { break; case 'n' : switch(str[2]) { break; case 'n' : switch(str[3]) { break; case 'n' : switch(str[4]) { break; case 'n' : s3 = "nnnnn"; } } } } 
            break; case 'o': switch(str[1]) { break; case 'o' : switch(str[2]) { break; case 'o' : switch(str[3]) { break; case 'o' : switch(str[4]) { break; case 'o' : s3 = "ooooo"; } } } } 
            break; case 'p': switch(str[1]) { break; case 'p' : switch(str[2]) { break; case 'p' : switch(str[3]) { break; case 'p' : switch(str[4]) { break; case 'p' : s3 = "ppppp"; } } } } 
            break; case 'q': switch(str[1]) { break; case 'q' : switch(str[2]) { break; case 'q' : switch(str[3]) { break; case 'q' : switch(str[4]) { break; case 'q' : s3 = "qqqqq"; } } } } 
            break; case 'r': switch(str[1]) { break; case 'r' : switch(str[2]) { break; case 'r' : switch(str[3]) { break; case 'r' : switch(str[4]) { break; case 'r' : s3 = "rrrrr"; } } } } 
            break; case 's': switch(str[1]) { break; case 's' : switch(str[2]) { break; case 's' : switch(str[3]) { break; case 's' : switch(str[4]) { break; case 's' : s3 = "sssss"; } } } } 
            break; case 't': switch(str[1]) { break; case 't' : switch(str[2]) { break; case 't' : switch(str[3]) { break; case 't' : switch(str[4]) { break; case 't' : s3 = "ttttt"; } } } } 
            break; case 'u': switch(str[1]) { break; case 'u' : switch(str[2]) { break; case 'u' : switch(str[3]) { break; case 'u' : switch(str[4]) { break; case 'u' : s3 = "uuuuu"; } } } } 
            break; case 'v': switch(str[1]) { break; case 'v' : switch(str[2]) { break; case 'v' : switch(str[3]) { break; case 'v' : switch(str[4]) { break; case 'v' : s3 = "vvvvv"; } } } } 
            break; case 'w': switch(str[1]) { break; case 'w' : switch(str[2]) { break; case 'w' : switch(str[3]) { break; case 'w' : switch(str[4]) { break; case 'w' : s3 = "wwwww"; } } } } 
            break; case 'x': switch(str[1]) { break; case 'x' : switch(str[2]) { break; case 'x' : switch(str[3]) { break; case 'x' : switch(str[4]) { break; case 'x' : s3 = "xxxxx"; } } } } 
            break; case 'y': switch(str[1]) { break; case 'y' : switch(str[2]) { break; case 'y' : switch(str[3]) { break; case 'y' : switch(str[4]) { break; case 'y' : s3 = "yyyyy"; } } } } 
            break; case 'z': switch(str[1]) { break; case 'z' : switch(str[2]) { break; case 'z' : switch(str[3]) { break; case 'z' : switch(str[4]) { break; case 'z' : s3 = "zzzzz"; } } } } 
            break; case 'a': switch(str[1]) { break; case 'a' : switch(str[2]) { break; case 'a' : switch(str[3]) { break; case 'a' : switch(str[4]) { break; case 'a' : s3 = "aaaaa"; } } } } 
            break; case 'b': switch(str[1]) { break; case 'b' : switch(str[2]) { break; case 'b' : switch(str[3]) { break; case 'b' : switch(str[4]) { break; case 'b' : s3 = "bbbbb"; } } } } 
            break; case 'c': switch(str[1]) { break; case 'c' : switch(str[2]) { break; case 'c' : switch(str[3]) { break; case 'c' : switch(str[4]) { break; case 'c' : s3 = "ccccc"; } } } } 
            break; case 'd': switch(str[1]) { break; case 'd' : switch(str[2]) { break; case 'd' : switch(str[3]) { break; case 'd' : switch(str[4]) { break; case 'd' : s3 = "ddddd"; } } } } 
            break; case 'e': switch(str[1]) { break; case 'e' : switch(str[2]) { break; case 'e' : switch(str[3]) { break; case 'e' : switch(str[4]) { break; case 'e' : s3 = "eeeee"; } } } } 
            break; case 'f': switch(str[1]) { break; case 'f' : switch(str[2]) { break; case 'f' : switch(str[3]) { break; case 'f' : switch(str[4]) { break; case 'f' : s3 = "fffff"; } } } } 
            break; case 'g': switch(str[1]) { break; case 'g' : switch(str[2]) { break; case 'g' : switch(str[3]) { break; case 'g' : switch(str[4]) { break; case 'g' : s3 = "ggggg"; } } } } 
            break; case 'h': switch(str[1]) { break; case 'h' : switch(str[2]) { break; case 'h' : switch(str[3]) { break; case 'h' : switch(str[4]) { break; case 'h' : s3 = "hhhhh"; } } } } 
            break; case 'i': switch(str[1]) { break; case 'i' : switch(str[2]) { break; case 'i' : switch(str[3]) { break; case 'i' : switch(str[4]) { break; case 'i' : s3 = "iiiii"; } } } } 
            break; case 'j': switch(str[1]) { break; case 'j' : switch(str[2]) { break; case 'j' : switch(str[3]) { break; case 'j' : switch(str[4]) { break; case 'j' : s3 = "jjjjj"; } } } } 
            break; case 'k': switch(str[1]) { break; case 'k' : switch(str[2]) { break; case 'k' : switch(str[3]) { break; case 'k' : switch(str[4]) { break; case 'k' : s3 = "kkkkk"; } } } } 
            break; case 'l': switch(str[1]) { break; case 'l' : switch(str[2]) { break; case 'l' : switch(str[3]) { break; case 'l' : switch(str[4]) { break; case 'l' : s3 = "lllll"; } } } } 
            break; case 'm': switch(str[1]) { break; case 'm' : switch(str[2]) { break; case 'm' : switch(str[3]) { break; case 'm' : switch(str[4]) { break; case 'm' : s3 = "mmmmm"; } } } } 
            break; case 'n': switch(str[1]) { break; case 'n' : switch(str[2]) { break; case 'n' : switch(str[3]) { break; case 'n' : switch(str[4]) { break; case 'n' : s3 = "nnnnn"; } } } } 
            break; case 'o': switch(str[1]) { break; case 'o' : switch(str[2]) { break; case 'o' : switch(str[3]) { break; case 'o' : switch(str[4]) { break; case 'o' : s3 = "ooooo"; } } } } 
            break; case 'p': switch(str[1]) { break; case 'p' : switch(str[2]) { break; case 'p' : switch(str[3]) { break; case 'p' : switch(str[4]) { break; case 'p' : s3 = "ppppp"; } } } } 
            break; case 'q': switch(str[1]) { break; case 'q' : switch(str[2]) { break; case 'q' : switch(str[3]) { break; case 'q' : switch(str[4]) { break; case 'q' : s3 = "qqqqq"; } } } } 
            break; case 'r': switch(str[1]) { break; case 'r' : switch(str[2]) { break; case 'r' : switch(str[3]) { break; case 'r' : switch(str[4]) { break; case 'r' : s3 = "rrrrr"; } } } } 
            break; case 's': switch(str[1]) { break; case 's' : switch(str[2]) { break; case 's' : switch(str[3]) { break; case 's' : switch(str[4]) { break; case 's' : s3 = "sssss"; } } } } 
            break; case 't': switch(str[1]) { break; case 't' : switch(str[2]) { break; case 't' : switch(str[3]) { break; case 't' : switch(str[4]) { break; case 't' : s3 = "ttttt"; } } } } 
            break; case 'u': switch(str[1]) { break; case 'u' : switch(str[2]) { break; case 'u' : switch(str[3]) { break; case 'u' : switch(str[4]) { break; case 'u' : s3 = "uuuuu"; } } } } 
            break; case 'v': switch(str[1]) { break; case 'v' : switch(str[2]) { break; case 'v' : switch(str[3]) { break; case 'v' : switch(str[4]) { break; case 'v' : s3 = "vvvvv"; } } } } 
            break; case 'w': switch(str[1]) { break; case 'w' : switch(str[2]) { break; case 'w' : switch(str[3]) { break; case 'w' : switch(str[4]) { break; case 'w' : s3 = "wwwww"; } } } } 
            break; case 'x': switch(str[1]) { break; case 'x' : switch(str[2]) { break; case 'x' : switch(str[3]) { break; case 'x' : switch(str[4]) { break; case 'x' : s3 = "xxxxx"; } } } } 
            break; case 'y': switch(str[1]) { break; case 'y' : switch(str[2]) { break; case 'y' : switch(str[3]) { break; case 'y' : switch(str[4]) { break; case 'y' : s3 = "yyyyy"; } } } } 
            break; case 'z': switch(str[1]) { break; case 'z' : switch(str[2]) { break; case 'z' : switch(str[3]) { break; case 'z' : switch(str[4]) { break; case 'z' : s3 = "zzzzz"; } } } } 
          }
        });
}

auto words_100_characters_5() {
  /*
   * 20 unique words (len==20)
   */
  std::string s;
  std::string str = "hdhoc";
  ankerl::nanobench::bench()
      .epochs(epochs)
      .minepochiterations(epoch_iterations)
      .run("100 unqiue words (len==5) - match", [&] {
        s = match(str) return "";
        case("dzynr") return "dzynr";
        case("hqtvk") return "hqtvk";
        case("qtezj") return "qtezj";
        case("muyfj") return "muyfj";
        case("pbyzl") return "pbyzl";
        case("ceode") return "ceode";
        case("efotw") return "efotw";
        case("hfzwr") return "hfzwr";
        case("wafbg") return "wafbg";
        case("vxbwe") return "vxbwe";
        case("nnzkl") return "nnzkl";
        case("thsfn") return "thsfn";
        case("psafh") return "psafh";
        case("lkmjg") return "lkmjg";
        case("pvejc") return "pvejc";
        case("agzju") return "agzju";
        case("blrlv") return "blrlv";
        case("ibpbf") return "ibpbf";
        case("lyxph") return "lyxph";
        case("pvvah") return "pvvah";
        case("clpot") return "clpot";
        case("nwjdn") return "nwjdn";
        case("glnkz") return "glnkz";
        case("utzwa") return "utzwa";
        case("vfyzt") return "vfyzt";
        case("muriw") return "muriw";
        case("xtxri") return "xtxri";
        case("pbcln") return "pbcln";
        case("wtcks") return "wtcks";
        case("cgzlg") return "cgzlg";
        case("rmvzm") return "rmvzm";
        case("bfkap") return "bfkap";
        case("twtut") return "twtut";
        case("jkwoy") return "jkwoy";
        case("grjjm") return "grjjm";
        case("dvxci") return "dvxci";
        case("xkwzr") return "xkwzr";
        case("mtyys") return "mtyys";
        case("kucok") return "kucok";
        case("xbvzu") return "xbvzu";
        case("cxdke") return "cxdke";
        case("kymwa") return "kymwa";
        case("hgfmt") return "hgfmt";
        case("ddsxq") return "ddsxq";
        case("rnzyj") return "rnzyj";
        case("pixce") return "pixce";
        case("xfnfl") return "xfnfl";
        case("avfhv") return "avfhv";
        case("gjgau") return "gjgau";
        case("zkzby") return "zkzby";
        case("nqbzo") return "nqbzo";
        case("pchcu") return "pchcu";
        case("iojjg") return "iojjg";
        case("wlalx") return "wlalx";
        case("jeoal") return "jeoal";
        case("dvuwx") return "dvuwx";
        case("exuoc") return "exuoc";
        case("anhto") return "anhto";
        case("auobj") return "auobj";
        case("goypx") return "goypx";
        case("zgosh") return "zgosh";
        case("mrlbo") return "mrlbo";
        case("ixyfg") return "ixyfg";
        case("eysxe") return "eysxe";
        case("vijea") return "vijea";
        case("jqyqd") return "jqyqd";
        case("aawlk") return "aawlk";
        case("pqdqs") return "pqdqs";
        case("taeis") return "taeis";
        case("rboth") return "rboth";
        case("wygkz") return "wygkz";
        case("yjiak") return "yjiak";
        case("tqqzl") return "tqqzl";
        case("gpbop") return "gpbop";
        case("ujnjg") return "ujnjg";
        case("ncmta") return "ncmta";
        case("rqheu") return "rqheu";
        case("ooqzx") return "ooqzx";
        case("uuzno") return "uuzno";
        case("pjlui") return "pjlui";
        case("hxniv") return "hxniv";
        case("igwve") return "igwve";
        case("expoj") return "expoj";
        case("poeqf") return "poeqf";
        case("ymgai") return "ymgai";
        case("ztzbj") return "ztzbj";
        case("rmoja") return "rmoja";
        case("ijvlh") return "ijvlh";
        case("mbqym") return "mbqym";
        case("xyqmo") return "xyqmo";
        case("rkmok") return "rkmok";
        case("bavkp") return "bavkp";
        case("dxjyy") return "dxjyy";
        case("yumwp") return "yumwp";
        case("mnfrp") return "mnfrp";
        case("fuwtz") return "fuwtz";
        case("gvbht") return "gvbht";
        case("hdtne") return "hdtne";
        case("exyes") return "exyes";
        case("hdhoc") return "hdhoc";
        endmatch;
      });

  ankerl::nanobench::bench()
      .epochs(epochs)
      .minepochiterations(epoch_iterations)
      .run("100 unique words (len==5) - if", [&] {
    if (str == "dzynr")
      s = "dzynr";
    else if (str == "hqtvk")
      s = "hqtvk";
    else if (str == "qtezj")
      s = "qtezj";
    else if (str == "muyfj")
      s = "muyfj";
    else if (str == "pbyzl")
      s = "pbyzl";
    else if (str == "ceode")
      s = "ceode";
    else if (str == "efotw")
      s = "efotw";
    else if (str == "hfzwr")
      s = "hfzwr";
    else if (str == "wafbg")
      s = "wafbg";
    else if (str == "vxbwe")
      s = "vxbwe";
    else if (str == "nnzkl")
      s = "nnzkl";
    else if (str == "thsfn")
      s = "thsfn";
    else if (str == "psafh")
      s = "psafh";
    else if (str == "lkmjg")
      s = "lkmjg";
    else if (str == "pvejc")
      s = "pvejc";
    else if (str == "agzju")
      s = "agzju";
    else if (str == "blrlv")
      s = "blrlv";
    else if (str == "ibpbf")
      s = "ibpbf";
    else if (str == "lyxph")
      s = "lyxph";
    else if (str == "pvvah")
      s = "pvvah";
    else if (str == "clpot")
      s = "clpot";
    else if (str == "nwjdn")
      s = "nwjdn";
    else if (str == "glnkz")
      s = "glnkz";
    else if (str == "utzwa")
      s = "utzwa";
    else if (str == "vfyzt")
      s = "vfyzt";
    else if (str == "muriw")
      s = "muriw";
    else if (str == "xtxri")
      s = "xtxri";
    else if (str == "pbcln")
      s = "pbcln";
    else if (str == "wtcks")
      s = "wtcks";
    else if (str == "cgzlg")
      s = "cgzlg";
    else if (str == "rmvzm")
      s = "rmvzm";
    else if (str == "bfkap")
      s = "bfkap";
    else if (str == "twtut")
      s = "twtut";
    else if (str == "jkwoy")
      s = "jkwoy";
    else if (str == "grjjm")
      s = "grjjm";
    else if (str == "dvxci")
      s = "dvxci";
    else if (str == "xkwzr")
      s = "xkwzr";
    else if (str == "mtyys")
      s = "mtyys";
    else if (str == "kucok")
      s = "kucok";
    else if (str == "xbvzu")
      s = "xbvzu";
    else if (str == "cxdke")
      s = "cxdke";
    else if (str == "kymwa")
      s = "kymwa";
    else if (str == "hgfmt")
      s = "hgfmt";
    else if (str == "ddsxq")
      s = "ddsxq";
    else if (str == "rnzyj")
      s = "rnzyj";
    else if (str == "pixce")
      s = "pixce";
    else if (str == "xfnfl")
      s = "xfnfl";
    else if (str == "avfhv")
      s = "avfhv";
    else if (str == "gjgau")
      s = "gjgau";
    else if (str == "zkzby")
      s = "zkzby";
    else if (str == "nqbzo")
      s = "nqbzo";
    else if (str == "pchcu")
      s = "pchcu";
    else if (str == "iojjg")
      s = "iojjg";
    else if (str == "wlalx")
      s = "wlalx";
    else if (str == "jeoal")
      s = "jeoal";
    else if (str == "dvuwx")
      s = "dvuwx";
    else if (str == "exuoc")
      s = "exuoc";
    else if (str == "anhto")
      s = "anhto";
    else if (str == "auobj")
      s = "auobj";
    else if (str == "goypx")
      s = "goypx";
    else if (str == "zgosh")
      s = "zgosh";
    else if (str == "mrlbo")
      s = "mrlbo";
    else if (str == "ixyfg")
      s = "ixyfg";
    else if (str == "eysxe")
      s = "eysxe";
    else if (str == "vijea")
      s = "vijea";
    else if (str == "jqyqd")
      s = "jqyqd";
    else if (str == "aawlk")
      s = "aawlk";
    else if (str == "pqdqs")
      s = "pqdqs";
    else if (str == "taeis")
      s = "taeis";
    else if (str == "rboth")
      s = "rboth";
    else if (str == "wygkz")
      s = "wygkz";
    else if (str == "yjiak")
      s = "yjiak";
    else if (str == "tqqzl")
      s = "tqqzl";
    else if (str == "gpbop")
      s = "gpbop";
    else if (str == "ujnjg")
      s = "ujnjg";
    else if (str == "ncmta")
      s = "ncmta";
    else if (str == "rqheu")
      s = "rqheu";
    else if (str == "ooqzx")
      s = "ooqzx";
    else if (str == "uuzno")
      s = "uuzno";
    else if (str == "pjlui")
      s = "pjlui";
    else if (str == "hxniv")
      s = "hxniv";
    else if (str == "igwve")
      s = "igwve";
    else if (str == "expoj")
      s = "expoj";
    else if (str == "poeqf")
      s = "poeqf";
    else if (str == "ymgai")
      s = "ymgai";
    else if (str == "ztzbj")
      s = "ztzbj";
    else if (str == "rmoja")
      s = "rmoja";
    else if (str == "ijvlh")
      s = "ijvlh";
    else if (str == "mbqym")
      s = "mbqym";
    else if (str == "xyqmo")
      s = "xyqmo";
    else if (str == "rkmok")
      s = "rkmok";
    else if (str == "bavkp")
      s = "bavkp";
    else if (str == "dxjyy")
      s = "dxjyy";
    else if (str == "yumwp")
      s = "yumwp";
    else if (str == "mnfrp")
      s = "mnfrp";
    else if (str == "fuwtz")
      s = "fuwtz";
    else if (str == "gvbht")
      s = "gvbht";
    else if (str == "hdtne")
      s = "hdtne";
    else if (str == "exyes")
      s = "exyes";
    else if (str == "hdhoc")
      s = "hdhoc";
  });
}

auto words_50_characters_32() {
  /*
   * 20 unique words (len==20)
   */
  std::string s;
  std::string str = "unllsklpooyycfsjotwogjgfvzmfiajb";
  ankerl::nanobench::bench()
      .epochs(epochs)
      .minepochiterations(epoch_iterations)
      .run("20 unique words (len==20) - match", [&] {
        s = match(str) return "";
        case("eitcsdvxlvzouyciqpophfgbgvpirntw") return "";
        case("bhcoplclvqpkouevodfpwmgbtappwgpx") return "";
        case("xgqdroupfrylpxslplwwizmcxiqvubew") return "";
        case("ucqsfqwjbypksmjjbxxolpfykzfbwkom") return "";
        case("uheugrqhzfhsnchpfqyklgwcmfqwhsyy") return "";
        case("emgadzrsxyygyatzqqusjsyrvtcrgppg") return "";
        case("dczfffnqcogarumqnotbnjjwnropayhv") return "";
        case("mekgkankopjlgttbfygxcpfmblgrwvef") return "";
        case("iqjrgpjzzkzvyudiaxhwpkrtcbxbjqsp") return "";
        case("xmjpkguxecyubvjcckylbwiuwtsqzoar") return "";
        case("gpqruisrkdujljfpihjhiufbwtxwstxt") return "";
        case("blhzvwaqauovulsmhdpqbsstygiabdfd") return "";
        case("rplwshprmfwcvisdahendviwynfovnte") return "";
        case("iumatqgjcxuzprqfiqeygrksbxanhaxy") return "";
        case("dntachpfzjjvggyrlrsexdgixutstuuu") return "";
        case("twsjlqljgrcqrooqhyojcgsvxlfvrepy") return "";
        case("hyddrdwbutxsqsuekvkqkzevrgaxiegv") return "";
        case("jcfhfqplmupjqqxbiaphqvffuglkthhx") return "";
        case("axipxlgndmmbsbydixzkxpszrnwbffae") return "";
        case("ycxcqqywjlbubfthyamzjeqgvrtckjzu") return "";
        case("myjmnkrrnpcekcfxmhugmrgccplnkzyd") return "";
        case("wtafsgrldqiyuboxlbtspptseqtgljus") return "";
        case("ixhohaulkljhohpjftalayvvjcjyhkhg") return "";
        case("rgtpjyuwilkvobrspzilgiovcdccsgdt") return "";
        case("xnmxtrlaximakmfgfcvyuozctjkzzwxn") return "";
        case("xtfwggqbuhlpjbmgsmyqaaomqgcyuxno") return "";
        case("epmnqzdgrnqacojhihzsiingcgiwzehl") return "";
        case("yltalusdemzelkekkcamkibfwuqxchks") return "";
        case("jhagiigfbvfprcruijbhimsgkweanvro") return "";
        case("sjzwcrfmcpzwwymjxkdoxceaacadbgpw") return "";
        case("cmtwvovnvdzdrdhiecmtbsaqdnzopzwz") return "";
        case("jfzkbzpnawgshkqjxacecohpruxsfutk") return "";
        case("huctomectqhpdoeykebreqnrqwpvdtvd") return "";
        case("igdcmlhktgyukebubfftwoizxwuhvvnz") return "";
        case("xgjqfneocrqzftpcssflqrqyfvenhgvj") return "";
        case("mkztphgoqonhfmkcsnnzdxncqychuypv") return "";
        case("yxhoomyvmbkgpcomqddbdvrvfesexstx") return "";
        case("uppkizbcqdmtgtbbwrquibmwycgincvm") return "";
        case("uicyjsqjaasmpmyqenmnhnkzrsidlftm") return "";
        case("cvgzvwifmdeulvzgapgiskkkygpdcfjy") return "";
        case("regktoyixsbgjbzihploxygrygwgitcj") return "";
        case("geejbrzehfkxdeffpryddibqjfhlxvxt") return "";
        case("dhanowaiutduosxbnmcmxvzjvqebiiic") return "";
        case("dkghuvhieknntngjqcdsuizcssbmrcsr") return "";
        case("bymzvhluvdrnfuxeiutyyxwadgeizojn") return "";
        case("sgjaxfopnrobnhiiumuldyeajtltnnzt") return "";
        case("njcgkkswbttllywlchireysgniyvvplh") return "";
        case("jdsnysqlhwqmphkuvuhtpjkqcmyqyvvd") return "";
        case("biwuqikumxqjqlynaylfpqgutxvwfgfu") return "";
        case("unllsklpooyycfsjotwogjgfvzmfiajb") return "";
        endmatch;
      });

  ankerl::nanobench::bench()
      .epochs(epochs)
      .minepochiterations(epoch_iterations)
      .run("20 unique words (len==20) - if", [&] {
        if (str == "eitcsdvxlvzouyciqpophfgbgvpirntw")
          s = "";
        else if (str == "bhcoplclvqpkouevodfpwmgbtappwgpx")
          s = "";
        else if (str == "xgqdroupfrylpxslplwwizmcxiqvubew")
          s = "";
        else if (str == "ucqsfqwjbypksmjjbxxolpfykzfbwkom")
          s = "";
        else if (str == "uheugrqhzfhsnchpfqyklgwcmfqwhsyy")
          s = "";
        else if (str == "emgadzrsxyygyatzqqusjsyrvtcrgppg")
          s = "";
        else if (str == "dczfffnqcogarumqnotbnjjwnropayhv")
          s = "";
        else if (str == "mekgkankopjlgttbfygxcpfmblgrwvef")
          s = "";
        else if (str == "iqjrgpjzzkzvyudiaxhwpkrtcbxbjqsp")
          s = "";
        else if (str == "xmjpkguxecyubvjcckylbwiuwtsqzoar")
          s = "";
        else if (str == "gpqruisrkdujljfpihjhiufbwtxwstxt")
          s = "";
        else if (str == "blhzvwaqauovulsmhdpqbsstygiabdfd")
          s = "";
        else if (str == "rplwshprmfwcvisdahendviwynfovnte")
          s = "";
        else if (str == "iumatqgjcxuzprqfiqeygrksbxanhaxy")
          s = "";
        else if (str == "dntachpfzjjvggyrlrsexdgixutstuuu")
          s = "";
        else if (str == "twsjlqljgrcqrooqhyojcgsvxlfvrepy")
          s = "";
        else if (str == "hyddrdwbutxsqsuekvkqkzevrgaxiegv")
          s = "";
        else if (str == "jcfhfqplmupjqqxbiaphqvffuglkthhx")
          s = "";
        else if (str == "axipxlgndmmbsbydixzkxpszrnwbffae")
          s = "";
        else if (str == "ycxcqqywjlbubfthyamzjeqgvrtckjzu")
          s = "";
        else if (str == "myjmnkrrnpcekcfxmhugmrgccplnkzyd")
          s = "";
        else if (str == "wtafsgrldqiyuboxlbtspptseqtgljus")
          s = "";
        else if (str == "ixhohaulkljhohpjftalayvvjcjyhkhg")
          s = "";
        else if (str == "rgtpjyuwilkvobrspzilgiovcdccsgdt")
          s = "";
        else if (str == "xnmxtrlaximakmfgfcvyuozctjkzzwxn")
          s = "";
        else if (str == "xtfwggqbuhlpjbmgsmyqaaomqgcyuxno")
          s = "";
        else if (str == "epmnqzdgrnqacojhihzsiingcgiwzehl")
          s = "";
        else if (str == "yltalusdemzelkekkcamkibfwuqxchks")
          s = "";
        else if (str == "jhagiigfbvfprcruijbhimsgkweanvro")
          s = "";
        else if (str == "sjzwcrfmcpzwwymjxkdoxceaacadbgpw")
          s = "";
        else if (str == "cmtwvovnvdzdrdhiecmtbsaqdnzopzwz")
          s = "";
        else if (str == "jfzkbzpnawgshkqjxacecohpruxsfutk")
          s = "";
        else if (str == "huctomectqhpdoeykebreqnrqwpvdtvd")
          s = "";
        else if (str == "igdcmlhktgyukebubfftwoizxwuhvvnz")
          s = "";
        else if (str == "xgjqfneocrqzftpcssflqrqyfvenhgvj")
          s = "";
        else if (str == "mkztphgoqonhfmkcsnnzdxncqychuypv")
          s = "";
        else if (str == "yxhoomyvmbkgpcomqddbdvrvfesexstx")
          s = "";
        else if (str == "uppkizbcqdmtgtbbwrquibmwycgincvm")
          s = "";
        else if (str == "uicyjsqjaasmpmyqenmnhnkzrsidlftm")
          s = "";
        else if (str == "cvgzvwifmdeulvzgapgiskkkygpdcfjy")
          s = "";
        else if (str == "regktoyixsbgjbzihploxygrygwgitcj")
          s = "";
        else if (str == "geejbrzehfkxdeffpryddibqjfhlxvxt")
          s = "";
        else if (str == "dhanowaiutduosxbnmcmxvzjvqebiiic")
          s = "";
        else if (str == "dkghuvhieknntngjqcdsuizcssbmrcsr")
          s = "";
        else if (str == "bymzvhluvdrnfuxeiutyyxwadgeizojn")
          s = "";
        else if (str == "sgjaxfopnrobnhiiumuldyeajtltnnzt")
          s = "";
        else if (str == "njcgkkswbttllywlchireysgniyvvplh")
          s = "";
        else if (str == "jdsnysqlhwqmphkuvuhtpjkqcmyqyvvd")
          s = "";
        else if (str == "biwuqikumxqjqlynaylfpqgutxvwfgfu")
          s = "";
        else if (str == "unllsklpooyycfsjotwogjgfvzmfiajb")
          s = "";
      });
}

auto words_20_length_20() {
  /*
   * 20 unique words (len==20)
   */
  std::string s;
  std::string str = "nkssesgrbxbqpdxxainx";
  ankerl::nanobench::bench()
      .epochs(epochs)
      .minepochiterations(epoch_iterations)
      .run("20 unique words (len==20) - match", [&] {
        s = match(str) return "";
        case("levqbzrsgghridatzhhg") return "";
        case("crdpqjgxzyvfpelidrdn") return "";
        case("jwvvkerzzwdtdacdpbfl") return "";
        case("mhggmgyyailfrhhuqckg") return "";
        case("jrlsecfgneabxyocetof") return "";
        case("llvksjwkfdxtohxjoqxb") return "";
        case("bljxhkqqixadrkzfygnn") return "";
        case("ulglrxxfhjpofaajmkmh") return "";
        case("uasrzepddiesphbaoqqf") return "";
        case("xdyfknnfmurqojdltitw") return "";
        case("olgbzibwutekkmibghxs") return "";
        case("qfzvjwflvjqfzmjfbmnw") return "";
        case("byiquhmrlctwelvpjojb") return "";
        case("ymoenssemtxtrcpvkoqi") return "";
        case("xxvxcycyfylnzbkvilhi") return "";
        case("yqneaphjbhaliztxypoj") return "";
        case("impjjncxydzlkmulizqf") return "";
        case("emwbwsdctqvgpnkrpawn") return "";
        case("ewgdqagjpovlqpvbjkrt") return "";
        case("nkssesgrbxbqpdxxainx") return "";
        endmatch;
      });

  ankerl::nanobench::bench()
      .epochs(epochs)
      .minepochiterations(epoch_iterations)
      .run("20 unique words (len==20) - if", [&] {
        if (str == "levqbzrsgghridatzhhg")
          s = "";
        else if (str == "crdpqjgxzyvfpelidrdn")
          s = "";
        else if (str == "jwvvkerzzwdtdacdpbfl")
          s = "";
        else if (str == "mhggmgyyailfrhhuqckg")
          s = "";
        else if (str == "jrlsecfgneabxyocetof")
          s = "";
        else if (str == "llvksjwkfdxtohxjoqxb")
          s = "";
        else if (str == "bljxhkqqixadrkzfygnn")
          s = "";
        else if (str == "ulglrxxfhjpofaajmkmh")
          s = "";
        else if (str == "uasrzepddiesphbaoqqf")
          s = "";
        else if (str == "xdyfknnfmurqojdltitw")
          s = "";
        else if (str == "olgbzibwutekkmibghxs")
          s = "";
        else if (str == "qfzvjwflvjqfzmjfbmnw")
          s = "";
        else if (str == "byiquhmrlctwelvpjojb")
          s = "";
        else if (str == "ymoenssemtxtrcpvkoqi")
          s = "";
        else if (str == "xxvxcycyfylnzbkvilhi")
          s = "";
        else if (str == "yqneaphjbhaliztxypoj")
          s = "";
        else if (str == "impjjncxydzlkmulizqf")
          s = "";
        else if (str == "emwbwsdctqvgpnkrpawn")
          s = "";
        else if (str == "ewgdqagjpovlqpvbjkrt")
          s = "";
        else if (str == "nkssesgrbxbqpdxxainx")
          s = "";
      });
}

int main() 
{
  words_26_characters_1();
  words_52_characters_1();
  words_26_characters_2();
  words_26_characters_3();
  words_26_characters_4();
  words_26_characters_5();
  words_52_characters_5();
  words_100_characters_5();
}


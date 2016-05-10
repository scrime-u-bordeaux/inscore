/* parser generated by jison 0.4.17 */
/*
  Returns a Parser object of the following structure:

  Parser: {
    yy: {}
  }

  Parser.prototype: {
    yy: {},
    trace: function(),
    symbols_: {associative list: name ==> number},
    terminals_: {associative list: number ==> name},
    productions_: [...],
    performAction: function anonymous(yytext, yyleng, yylineno, yy, yystate, $$, _$),
    table: [...],
    defaultActions: {...},
    parseError: function(str, hash),
    parse: function(input),

    lexer: {
        EOF: 1,
        parseError: function(str, hash),
        setInput: function(input),
        input: function(),
        unput: function(str),
        more: function(),
        less: function(n),
        pastInput: function(),
        upcomingInput: function(),
        showPosition: function(),
        test_match: function(regex_match_array, rule_index),
        next: function(),
        lex: function(),
        begin: function(condition),
        popState: function(),
        _currentRules: function(),
        topState: function(),
        pushState: function(condition),

        options: {
            ranges: boolean           (optional: true ==> token location info will include a .range[] member)
            flex: boolean             (optional: true ==> flex-like lexing behaviour where the rules are tested exhaustively to find the longest match)
            backtrack_lexer: boolean  (optional: true ==> lexer regexes are tested in order and for each matching regex the action code is invoked; the lexer terminates the scan when a token is returned by the action code)
        },

        performAction: function(yy, yy_, $avoiding_name_collisions, YY_START),
        rules: [...],
        conditions: {associative list: name ==> set},
    }
  }


  token location info (@$, _$, etc.): {
    first_line: n,
    last_line: n,
    first_column: n,
    last_column: n,
    range: [start_number, end_number]       (where the numbers are indexes into the input string, regular zero-based)
  }


  the parseError function receives a 'hash' object with these members for lexer and parser errors: {
    text:        (matched text)
    token:       (the produced terminal token, if any)
    line:        (yylineno)
  }
  while parser (grammar) errors will also provide these members, i.e. parser errors deliver a superset of attributes: {
    loc:         (yylloc)
    expected:    (string describing the set of expected tokens)
    recoverable: (boolean: TRUE when the parser has a error recovery rule available for this particular error)
  }
*/
var INScoreParser = (function(){
var o=function(k,v,o,l){for(o=o||{},l=k.length;l--;o[k[l]]=v);return o},$V0=[1,6],$V1=[1,9],$V2=[1,10],$V3=[1,14],$V4=[1,16],$V5=[1,17],$V6=[1,13],$V7=[1,9,10,21,24,27,28,31],$V8=[6,16,19,20],$V9=[1,32],$Va=[1,26],$Vb=[1,31],$Vc=[1,35],$Vd=[1,36],$Ve=[1,34],$Vf=[1,25],$Vg=[1,27],$Vh=[1,29],$Vi=[1,30],$Vj=[2,23],$Vk=[6,10,13,14,16,19,20,26,28,31,32,34,35,36,37,38],$Vl=[6,10,14,16,19,20,26,28,31,32,34,35,36,37,38],$Vm=[1,57],$Vn=[1,58],$Vo=[16,19,20],$Vp=[21,24,27,28,31];
var parser = {trace: function trace() { },
yy: {},
symbols_: {"error":2,"inscore":3,"expr":4,"message":5,"ENDEXPR":6,"variabledecl":7,"script":8,"ENDSCRIPT":9,"JSCRIPT":10,"address":11,"params":12,"eval":13,"LEFTPAR":14,"messagelist":15,"RIGHTPAR":16,"variable":17,"messagelistseparator":18,"COMMA":19,"COLON":20,"OSCADDRESS":21,"relativeaddress":22,"urlprefix":23,"POINT":24,"hostname":25,"UINT":26,"IPNUM":27,"HOSTNAME":28,"varname":29,"identifier":30,"IDENTIFIER":31,"REGEXP":32,"param":33,"VARSTART":34,"INT":35,"FLOAT":36,"STRING":37,"EXPRESSION":38,"EQUAL":39,"$accept":0,"$end":1},
terminals_: {2:"error",6:"ENDEXPR",9:"ENDSCRIPT",10:"JSCRIPT",13:"eval",14:"LEFTPAR",16:"RIGHTPAR",19:"COMMA",20:"COLON",21:"OSCADDRESS",24:"POINT",26:"UINT",27:"IPNUM",28:"HOSTNAME",31:"IDENTIFIER",32:"REGEXP",34:"VARSTART",35:"INT",36:"FLOAT",37:"STRING",38:"EXPRESSION",39:"EQUAL"},
productions_: [0,[3,1],[3,2],[4,2],[4,2],[4,1],[4,1],[8,1],[5,1],[5,2],[5,5],[5,3],[15,1],[15,3],[18,1],[18,1],[11,1],[11,1],[11,2],[22,2],[23,3],[23,3],[25,1],[25,1],[30,1],[30,1],[12,1],[12,1],[12,2],[12,2],[17,2],[17,4],[33,1],[33,1],[33,1],[33,1],[33,1],[33,1],[33,1],[33,3],[33,1],[7,3],[29,1]],
performAction: function anonymous(yytext, yyleng, yylineno, yy, yystate /* action[1] */, $$ /* vstack */, _$ /* lstack */) {
/* this == yyval */

var $0 = $$.length - 1;
switch (yystate) {
case 3:
 parser.msgs.push($$[$0-1]); 
break;
case 4: case 5:
 
break;
case 6:
 debugyacc("expr ENDSCRIPT "); return true; 
break;
case 7:
 if ($$[$0].length) rparse (array2string(context_eval($$[$0]) )); 
break;
case 8:
 this.$ = new Message($$[$0], new Array()); 
break;
case 9:
 this.$ = new Message($$[$0-1], $$[$0]); debugyacc(this.$.toString()); 
break;
case 10:
 $$[$0-1].unshift($$[$0-3]); this.$ = new Message($$[$0-4], $$[$0-1]); 
break;
case 11:
 $$[$0].unshift($$[$0-1]); this.$ = new Message($$[$0-2], $$[$0]); 
break;
case 12: case 26:
 this.$ = new Array(); this.$.push($$[$0]); 
break;
case 13:
 $$[$0-2].push($$[$0]); this.$ = $$[$0-2]; 
break;
case 16:
 this.$ = new Address("", 0, $$[$0]); debugyacc("OSCADDRESS: -"+$$[$0]+"-"); 
break;
case 17:
 this.$ = new Address("", 0, $$[$0]);
break;
case 18:
 $$[$0-1].osc = $$[$0]; this.$ = $$[$0-1]; 
break;
case 19:
 this.$ = $$[$0-1] + $$[$0]; 
break;
case 20: case 21:
 this.$ = new Address($$[$0-2], parseInt($$[$0]), ""); 
break;
case 22: case 23: case 24: case 25: case 27: case 35: case 36: case 37: case 38: case 40: case 42:
 this.$ = $$[$0]; 
break;
case 28:
 this.$ = $$[$0-1].concat($$[$0]); 
break;
case 29:
 $$[$0-1].push($$[$0]); this.$ = $$[$0-1]; 
break;
case 30:
 this.$ = parser.vars[$$[$0]]; 
break;
case 31:
 this.$ = new Array($$[$0-1]); 
break;
case 32: case 33:
 this.$ = parseInt($$[$0]); 
break;
case 34:
 this.$ = parseFloat($$[$0]); 
break;
case 39:
 this.$ = $$[$0-1]; 
break;
case 41:
 debugyacc("variabledecl: " + $$[$0-2] + " = " + $$[$0]); parser.vars[$$[$0-2]] = $$[$0]; 
break;
}
},
table: [{3:1,4:2,5:3,7:4,8:5,9:$V0,10:$V1,11:7,21:$V2,22:11,23:12,24:$V3,25:15,27:$V4,28:$V5,29:8,31:$V6},{1:[3],4:18,5:3,7:4,8:5,9:$V0,10:$V1,11:7,21:$V2,22:11,23:12,24:$V3,25:15,27:$V4,28:$V5,29:8,31:$V6},o($V7,[2,1]),{6:[1,19]},{6:[1,20]},o($V7,[2,5]),o($V7,[2,6]),o($V8,[2,8],{12:21,33:23,17:24,30:28,8:33,10:$V1,13:[1,22],14:$V9,26:$Va,28:$Vb,31:$Vc,32:$Vd,34:$Ve,35:$Vf,36:$Vg,37:$Vh,38:$Vi}),{20:$Vj,39:[1,37]},o([1,6,9,10,14,16,19,20,21,24,26,27,28,31,32,34,35,36,37,38],[2,7]),o($Vk,[2,16]),o($Vk,[2,17]),{21:[1,38]},o([6,10,14,16,19,20,26,28,31,32,34,35,36,37,38,39],[2,42]),{21:[1,39]},{20:[1,40]},{20:[1,41]},{20:[2,22]},o($V7,[2,2]),o($V7,[2,3]),o($V7,[2,4]),o($V8,[2,9],{30:28,8:33,17:42,33:43,10:$V1,14:$V9,26:$Va,28:$Vb,31:$Vc,32:$Vd,34:$Ve,35:$Vf,36:$Vg,37:$Vh,38:$Vi}),{14:[1,44],17:45,34:$Ve},o($Vl,[2,26]),o($Vl,[2,27]),o($Vl,[2,32]),o($Vl,[2,33]),o($Vl,[2,34]),o($Vl,[2,35]),o($Vl,[2,36]),o($Vl,[2,37]),o($Vl,[2,38]),{5:47,11:7,15:46,21:$V2,22:11,23:12,24:$V3,25:15,27:$V4,28:$V5,29:48,31:$V6},o($Vl,[2,40]),{14:[1,50],29:49,31:$V6},o($Vl,[2,24]),o($Vl,[2,25]),{8:33,10:$V1,12:51,14:$V9,17:24,26:$Va,28:$Vb,30:28,31:$Vc,32:$Vd,33:23,34:$Ve,35:$Vf,36:$Vg,37:$Vh,38:$Vi},o($Vk,[2,18]),o($Vk,[2,19]),{26:[1,52]},{26:[1,53]},o($Vl,[2,28]),o($Vl,[2,29]),{5:47,11:7,15:54,21:$V2,22:11,23:12,24:$V3,25:15,27:$V4,28:$V5,29:48,31:$V6},o($V8,[2,11]),{16:[1,55],18:56,19:$Vm,20:$Vn},o($Vo,[2,12]),{20:$Vj},o($Vl,[2,30]),{5:59,11:7,21:$V2,22:11,23:12,24:$V3,25:15,27:$V4,28:$V5,29:48,31:$V6},{6:[2,41],8:33,10:$V1,14:$V9,17:42,26:$Va,28:$Vb,30:28,31:$Vc,32:$Vd,33:43,34:$Ve,35:$Vf,36:$Vg,37:$Vh,38:$Vi},{21:[2,20]},{21:[2,21]},{16:[1,60],18:56,19:$Vm,20:$Vn},o($Vl,[2,39]),{5:61,11:7,21:$V2,22:11,23:12,24:$V3,25:15,27:$V4,28:$V5,29:48,31:$V6},o($Vp,[2,14]),o($Vp,[2,15]),{16:[1,62]},o($V8,[2,10]),o($Vo,[2,13]),o($Vl,[2,31])],
defaultActions: {17:[2,22],48:[2,23],52:[2,20],53:[2,21]},
parseError: function parseError(str, hash) {
    if (hash.recoverable) {
        this.trace(str);
    } else {
        function _parseError (msg, hash) {
            this.message = msg;
            this.hash = hash;
        }
        _parseError.prototype = Error;

        throw new _parseError(str, hash);
    }
},
parse: function parse(input) {
    var self = this, stack = [0], tstack = [], vstack = [null], lstack = [], table = this.table, yytext = '', yylineno = 0, yyleng = 0, recovering = 0, TERROR = 2, EOF = 1;
    var args = lstack.slice.call(arguments, 1);
    var lexer = Object.create(this.lexer);
    var sharedState = { yy: {} };
    for (var k in this.yy) {
        if (Object.prototype.hasOwnProperty.call(this.yy, k)) {
            sharedState.yy[k] = this.yy[k];
        }
    }
    lexer.setInput(input, sharedState.yy);
    sharedState.yy.lexer = lexer;
    sharedState.yy.parser = this;
    if (typeof lexer.yylloc == 'undefined') {
        lexer.yylloc = {};
    }
    var yyloc = lexer.yylloc;
    lstack.push(yyloc);
    var ranges = lexer.options && lexer.options.ranges;
    if (typeof sharedState.yy.parseError === 'function') {
        this.parseError = sharedState.yy.parseError;
    } else {
        this.parseError = Object.getPrototypeOf(this).parseError;
    }
    function popStack(n) {
        stack.length = stack.length - 2 * n;
        vstack.length = vstack.length - n;
        lstack.length = lstack.length - n;
    }
    _token_stack:
        var lex = function () {
            var token;
            token = lexer.lex() || EOF;
            if (typeof token !== 'number') {
                token = self.symbols_[token] || token;
            }
            return token;
        };
    var symbol, preErrorSymbol, state, action, a, r, yyval = {}, p, len, newState, expected;
    while (true) {
        state = stack[stack.length - 1];
        if (this.defaultActions[state]) {
            action = this.defaultActions[state];
        } else {
            if (symbol === null || typeof symbol == 'undefined') {
                symbol = lex();
            }
            action = table[state] && table[state][symbol];
        }
                    if (typeof action === 'undefined' || !action.length || !action[0]) {
                var errStr = '';
                expected = [];
                for (p in table[state]) {
                    if (this.terminals_[p] && p > TERROR) {
                        expected.push('\'' + this.terminals_[p] + '\'');
                    }
                }
                if (lexer.showPosition) {
                    errStr = 'Parse error on line ' + (yylineno + 1) + ':\n' + lexer.showPosition() + '\nExpecting ' + expected.join(', ') + ', got \'' + (this.terminals_[symbol] || symbol) + '\'';
                } else {
                    errStr = 'Parse error on line ' + (yylineno + 1) + ': Unexpected ' + (symbol == EOF ? 'end of input' : '\'' + (this.terminals_[symbol] || symbol) + '\'');
                }
                this.parseError(errStr, {
                    text: lexer.match,
                    token: this.terminals_[symbol] || symbol,
                    line: lexer.yylineno,
                    loc: yyloc,
                    expected: expected
                });
            }
        if (action[0] instanceof Array && action.length > 1) {
            throw new Error('Parse Error: multiple actions possible at state: ' + state + ', token: ' + symbol);
        }
        switch (action[0]) {
        case 1:
            stack.push(symbol);
            vstack.push(lexer.yytext);
            lstack.push(lexer.yylloc);
            stack.push(action[1]);
            symbol = null;
            if (!preErrorSymbol) {
                yyleng = lexer.yyleng;
                yytext = lexer.yytext;
                yylineno = lexer.yylineno;
                yyloc = lexer.yylloc;
                if (recovering > 0) {
                    recovering--;
                }
            } else {
                symbol = preErrorSymbol;
                preErrorSymbol = null;
            }
            break;
        case 2:
            len = this.productions_[action[1]][1];
            yyval.$ = vstack[vstack.length - len];
            yyval._$ = {
                first_line: lstack[lstack.length - (len || 1)].first_line,
                last_line: lstack[lstack.length - 1].last_line,
                first_column: lstack[lstack.length - (len || 1)].first_column,
                last_column: lstack[lstack.length - 1].last_column
            };
            if (ranges) {
                yyval._$.range = [
                    lstack[lstack.length - (len || 1)].range[0],
                    lstack[lstack.length - 1].range[1]
                ];
            }
            r = this.performAction.apply(yyval, [
                yytext,
                yyleng,
                yylineno,
                sharedState.yy,
                action[1],
                vstack,
                lstack
            ].concat(args));
            if (typeof r !== 'undefined') {
                return r;
            }
            if (len) {
                stack = stack.slice(0, -1 * len * 2);
                vstack = vstack.slice(0, -1 * len);
                lstack = lstack.slice(0, -1 * len);
            }
            stack.push(this.productions_[action[1]][0]);
            vstack.push(yyval.$);
            lstack.push(yyval._$);
            newState = table[stack[stack.length - 2]][stack[stack.length - 1]];
            stack.push(newState);
            break;
        case 3:
            return true;
        }
    }
    return true;
}};

	function debugyacc(str){
//		typeof console !== 'undefined' ? console.log(str) : print(str);
	}
	function array2string(a){
		if (typeof a == "string") return a;
		if (typeof a == "object") {
			let out = "";
			for (let i=0; i<a.length; i++) {
				out += array2string(a[i]) + "\n";
			}
			return out;
		}
		return "";
	}
	function rparse(str){
		if (!str.length) return;
		INScoreParser.parse (str);
	}
	function context_vars(){
		let vars = parser.vars;
		let out  = "";
		for (let key in vars)
			out += "var " + key + "=" + vars[key][0].toString() + ";\n";
		return out;
	}
	function context_eval(str){
		var gInscoreParserContext = this;
		this['print'] = function (s) { console.log(s); }
		return gInscoreParserContext.eval( context_vars() + str);
	}

parser.msgs = new Array;
parser.vars = new Array;

function Address (ip, port, osc) {
	this.ip = ip;				// a string
	this.port = port;			// an integer
	this.osc = osc;				// a string
	this.toString = function() { return this.ip + (this.port ? (":" + this.port) : "") + this.osc; }
}

function Message (addr, params) {
	this.address = addr;		// a prototyped array (see below)
	this.params = params;		// an array
	this.toString = function() { return this.address.toString() + " " + this.params.toString(); }
}

parser.get = (function () {
	var msgs = parser.msgs;
	parser.msgs = [];
	parser.vars = [];
	return msgs;
})

parser.parseError = function(str, hash) {
	typeof console !== 'undefined' ? console.log(str) : print(str);
}
/* generated by jison-lex 0.3.4 */
var lexer = (function(){
var lexer = ({

EOF:1,

parseError:function parseError(str, hash) {
        if (this.yy.parser) {
            this.yy.parser.parseError(str, hash);
        } else {
            throw new Error(str);
        }
    },

// resets the lexer, sets new input
setInput:function (input, yy) {
        this.yy = yy || this.yy || {};
        this._input = input;
        this._more = this._backtrack = this.done = false;
        this.yylineno = this.yyleng = 0;
        this.yytext = this.matched = this.match = '';
        this.conditionStack = ['INITIAL'];
        this.yylloc = {
            first_line: 1,
            first_column: 0,
            last_line: 1,
            last_column: 0
        };
        if (this.options.ranges) {
            this.yylloc.range = [0,0];
        }
        this.offset = 0;
        return this;
    },

// consumes and returns one char from the input
input:function () {
        var ch = this._input[0];
        this.yytext += ch;
        this.yyleng++;
        this.offset++;
        this.match += ch;
        this.matched += ch;
        var lines = ch.match(/(?:\r\n?|\n).*/g);
        if (lines) {
            this.yylineno++;
            this.yylloc.last_line++;
        } else {
            this.yylloc.last_column++;
        }
        if (this.options.ranges) {
            this.yylloc.range[1]++;
        }

        this._input = this._input.slice(1);
        return ch;
    },

// unshifts one char (or a string) into the input
unput:function (ch) {
        var len = ch.length;
        var lines = ch.split(/(?:\r\n?|\n)/g);

        this._input = ch + this._input;
        this.yytext = this.yytext.substr(0, this.yytext.length - len);
        //this.yyleng -= len;
        this.offset -= len;
        var oldLines = this.match.split(/(?:\r\n?|\n)/g);
        this.match = this.match.substr(0, this.match.length - 1);
        this.matched = this.matched.substr(0, this.matched.length - 1);

        if (lines.length - 1) {
            this.yylineno -= lines.length - 1;
        }
        var r = this.yylloc.range;

        this.yylloc = {
            first_line: this.yylloc.first_line,
            last_line: this.yylineno + 1,
            first_column: this.yylloc.first_column,
            last_column: lines ?
                (lines.length === oldLines.length ? this.yylloc.first_column : 0)
                 + oldLines[oldLines.length - lines.length].length - lines[0].length :
              this.yylloc.first_column - len
        };

        if (this.options.ranges) {
            this.yylloc.range = [r[0], r[0] + this.yyleng - len];
        }
        this.yyleng = this.yytext.length;
        return this;
    },

// When called from action, caches matched text and appends it on next action
more:function () {
        this._more = true;
        return this;
    },

// When called from action, signals the lexer that this rule fails to match the input, so the next matching rule (regex) should be tested instead.
reject:function () {
        if (this.options.backtrack_lexer) {
            this._backtrack = true;
        } else {
            return this.parseError('Lexical error on line ' + (this.yylineno + 1) + '. You can only invoke reject() in the lexer when the lexer is of the backtracking persuasion (options.backtrack_lexer = true).\n' + this.showPosition(), {
                text: "",
                token: null,
                line: this.yylineno
            });

        }
        return this;
    },

// retain first n characters of the match
less:function (n) {
        this.unput(this.match.slice(n));
    },

// displays already matched input, i.e. for error messages
pastInput:function () {
        var past = this.matched.substr(0, this.matched.length - this.match.length);
        return (past.length > 20 ? '...':'') + past.substr(-20).replace(/\n/g, "");
    },

// displays upcoming input, i.e. for error messages
upcomingInput:function () {
        var next = this.match;
        if (next.length < 20) {
            next += this._input.substr(0, 20-next.length);
        }
        return (next.substr(0,20) + (next.length > 20 ? '...' : '')).replace(/\n/g, "");
    },

// displays the character position where the lexing error occurred, i.e. for error messages
showPosition:function () {
        var pre = this.pastInput();
        var c = new Array(pre.length + 1).join("-");
        return pre + this.upcomingInput() + "\n" + c + "^";
    },

// test the lexed token: return FALSE when not a match, otherwise return token
test_match:function (match, indexed_rule) {
        var token,
            lines,
            backup;

        if (this.options.backtrack_lexer) {
            // save context
            backup = {
                yylineno: this.yylineno,
                yylloc: {
                    first_line: this.yylloc.first_line,
                    last_line: this.last_line,
                    first_column: this.yylloc.first_column,
                    last_column: this.yylloc.last_column
                },
                yytext: this.yytext,
                match: this.match,
                matches: this.matches,
                matched: this.matched,
                yyleng: this.yyleng,
                offset: this.offset,
                _more: this._more,
                _input: this._input,
                yy: this.yy,
                conditionStack: this.conditionStack.slice(0),
                done: this.done
            };
            if (this.options.ranges) {
                backup.yylloc.range = this.yylloc.range.slice(0);
            }
        }

        lines = match[0].match(/(?:\r\n?|\n).*/g);
        if (lines) {
            this.yylineno += lines.length;
        }
        this.yylloc = {
            first_line: this.yylloc.last_line,
            last_line: this.yylineno + 1,
            first_column: this.yylloc.last_column,
            last_column: lines ?
                         lines[lines.length - 1].length - lines[lines.length - 1].match(/\r?\n?/)[0].length :
                         this.yylloc.last_column + match[0].length
        };
        this.yytext += match[0];
        this.match += match[0];
        this.matches = match;
        this.yyleng = this.yytext.length;
        if (this.options.ranges) {
            this.yylloc.range = [this.offset, this.offset += this.yyleng];
        }
        this._more = false;
        this._backtrack = false;
        this._input = this._input.slice(match[0].length);
        this.matched += match[0];
        token = this.performAction.call(this, this.yy, this, indexed_rule, this.conditionStack[this.conditionStack.length - 1]);
        if (this.done && this._input) {
            this.done = false;
        }
        if (token) {
            return token;
        } else if (this._backtrack) {
            // recover context
            for (var k in backup) {
                this[k] = backup[k];
            }
            return false; // rule action called reject() implying the next rule should be tested instead.
        }
        return false;
    },

// return next match in input
next:function () {
        if (this.done) {
            return this.EOF;
        }
        if (!this._input) {
            this.done = true;
        }

        var token,
            match,
            tempMatch,
            index;
        if (!this._more) {
            this.yytext = '';
            this.match = '';
        }
        var rules = this._currentRules();
        for (var i = 0; i < rules.length; i++) {
            tempMatch = this._input.match(this.rules[rules[i]]);
            if (tempMatch && (!match || tempMatch[0].length > match[0].length)) {
                match = tempMatch;
                index = i;
                if (this.options.backtrack_lexer) {
                    token = this.test_match(tempMatch, rules[i]);
                    if (token !== false) {
                        return token;
                    } else if (this._backtrack) {
                        match = false;
                        continue; // rule action called reject() implying a rule MISmatch.
                    } else {
                        // else: this is a lexer rule which consumes input without producing a token (e.g. whitespace)
                        return false;
                    }
                } else if (!this.options.flex) {
                    break;
                }
            }
        }
        if (match) {
            token = this.test_match(match, rules[index]);
            if (token !== false) {
                return token;
            }
            // else: this is a lexer rule which consumes input without producing a token (e.g. whitespace)
            return false;
        }
        if (this._input === "") {
            return this.EOF;
        } else {
            return this.parseError('Lexical error on line ' + (this.yylineno + 1) + '. Unrecognized text.\n' + this.showPosition(), {
                text: "",
                token: null,
                line: this.yylineno
            });
        }
    },

// return next match that has a token
lex:function lex() {
        var r = this.next();
        if (r) {
            return r;
        } else {
            return this.lex();
        }
    },

// activates a new lexer condition state (pushes the new lexer condition state onto the condition stack)
begin:function begin(condition) {
        this.conditionStack.push(condition);
    },

// pop the previously active lexer condition state off the condition stack
popState:function popState() {
        var n = this.conditionStack.length - 1;
        if (n > 0) {
            return this.conditionStack.pop();
        } else {
            return this.conditionStack[0];
        }
    },

// produce the lexer rule set which is active for the currently active lexer condition state
_currentRules:function _currentRules() {
        if (this.conditionStack.length && this.conditionStack[this.conditionStack.length - 1]) {
            return this.conditions[this.conditionStack[this.conditionStack.length - 1]].rules;
        } else {
            return this.conditions["INITIAL"].rules;
        }
    },

// return the currently active lexer condition state; when an index argument is provided it produces the N-th previous condition state, if available
topState:function topState(n) {
        n = this.conditionStack.length - 1 - Math.abs(n || 0);
        if (n >= 0) {
            return this.conditionStack[n];
        } else {
            return "INITIAL";
        }
    },

// alias for begin(condition)
pushState:function pushState(condition) {
        this.begin(condition);
    },

// return the number of states currently on the stack
stateStackSize:function stateStackSize() {
        return this.conditionStack.length;
    },
options: {"flex":true},
performAction: function anonymous(yy,yy_,$avoiding_name_collisions,YY_START) {
function debuglex(str){
//	typeof console !== 'undefined' ? console.log("  lex: " + str) : print("  lex: " + str);
}

// ----------------------------------------------------------------------------------------
// strip escape char '\' from escaped characters
function unescape (str) {
	var n = str.length;
	var outStr = "";
	// browse the string:  'r' is an index to the current read location
	//                     'w' is an index to the current write location
	for (r=0, w=0; r < n; r++) {		
		if (str[r] == '\\') {			// escape char '\' is found
			var next = str[r+1];
			if ((next != '\'') && (next != '"')) {	// escape only ' and "
				outStr += str[r];		// output the escape char 
			}
		}
		else outStr += str[r];			// no escape: put the current char at write location 
	}
 	return outStr;
}

var YYSTATE=YY_START;
switch($avoiding_name_collisions) {
case 0:return 26;
break;
case 1:return 26;
break;
case 2:return 35;
break;
case 3:return 36;
break;
case 4:return 36;
break;
case 5:return 36;
break;
case 6:debuglex("ENDSCRIPT : " + yy_.yytext); return 9;
break;
case 7:debuglex("IDENTIFIER: " + yy_.yytext); return 31;
break;
case 8:debuglex("HOSTNAME: " + yy_.yytext); return 28;
break;
case 9:debuglex("IPNUM: " + yy_.yytext); return 27;
break;
case 10:return 'EVAL';
break;
case 11:this.begin('DQSTR');
break;
case 12: debuglex ("STRING: " + unescape(yy_.yytext)); return 37; 
break;
case 13:this.popState();
break;
case 14:this.begin('QSTR');
break;
case 15: debuglex ("STRING: " + unescape(yy_.yytext)); return 37; 
break;
case 16:this.popState();
break;
case 17: debuglex ("FILE STRING: " + yy_.yytext);	return 37; 
break;
case 18:this.begin('JSECTION');
break;
case 19:this.popState();
break;
case 20: debuglex ("JAVASCRIPT: " + yy_.yytext); return 10; 
break;
case 21: debuglex ("REGEXP: " + yy_.yytext); return 32; 
break;
case 22: debuglex ("REGEXP: " + yy_.yytext); return 32; 
break;
case 23: debuglex ("REGEXP: " + yy_.yytext); return 32; 
break;
case 24: this.more(); this.begin('EXPRSECTION'); 
break;
case 25: this.more(); this.popState(); 
							if (this.topState() == 'INITIAL') {
							debuglex("EXPRESSION " + yy_.yytext);
							return 38; 
							}
						
break;
case 26: this.more(); 
break;
case 27: this.begin('EXPRSECTION'); this.more(); 
break;
case 28: this.more(); this.begin('OSCSECTION'); 
break;
case 29: this.more(); 
break;
case 30: this.more(); 
break;
case 31: this.more(); 
break;
case 32: this.more(); 
break;
case 33: this.more(); 
break;
case 34: debuglex("OSCADDRESS " + yy_.yytext); this.popState(); yy_.yytext = yy_.yytext.substring(0, yy_.yytext.length-1); return 21; 
break;
case 35:return 39;
break;
case 36:return 6;			/* end of expression */
break;
case 37:return 34;
break;
case 38:return 20;
break;
case 39:return 19;
break;
case 40:return 24;
break;
case 41:return 14;
break;
case 42:return 16;
break;
case 43:debuglex ("COMMENTLINE: " + yy_.yytext); 
break;
case 44:debuglex ("COMMENTLINE: " + yy_.yytext); 
break;
case 45:;
break;
case 46: debuglex ("BEGIN NESTED COMMENT"); this.begin('COMMENT'); 
break;
case 47: debuglex ("END COMMENT"); this.popState(); 
break;
case 48: debuglex ("BEGIN COMMENT"); this.begin('COMMENT'); 
break;
case 49:;   /* eat up space */
break;
case 50:;	/* yy_.yylloc->first_column=0; ignore */
break;
case 51:return 9;
break;
case 52: debuglex("ERR: " + yy_.yytext); return 'ERR'; 
break;
case 53:console.log(yy_.yytext);
break;
}
},
rules: [/^(?:([0-9])+)/,/^(?:\+([0-9])+)/,/^(?:-([0-9])+)/,/^(?:[+-]?([0-9])+\.([0-9])*)/,/^(?:[+-]?([0-9])+\.([0-9])+e[-+]?([0-9])+)/,/^(?:[+-]?([0-9])+e[-+]?([0-9])+)/,/^(?:__END__)/,/^(?:([_a-zA-Z])([_a-zA-Z0-9])*)/,/^(?:(([-a-zA-Z0-9])(([-a-zA-Z0-9])*|\.))+)/,/^(?:([0-9])+\.([0-9])+\.([0-9])+\.([0-9])+)/,/^(?:eval)/,/^(?:")/,/^(?:(\\"|[^"])*)/,/^(?:")/,/^(?:')/,/^(?:(\\'|[^'])*)/,/^(?:')/,/^(?:(\/|(\.\.?\/)*)(([^ \t\\/?:*><|"'!#;=])+\/?)+\.[a-zA-Z]+)/,/^(?:<\?([ \t])*javascript)/,/^(?:\?>)/,/^(?:(([\x0a\x0d])|\?[^>]|[^?])*)/,/^(?:([-_a-zA-Z0-9?+*])+)/,/^(?:([-_a-zA-Z0-9?+*])*\[([-_a-zA-Z0-9^])+\]([-_a-zA-Z0-9?+*])*)/,/^(?:([-_a-zA-Z0-9?+*])*\{[_a-zA-Z0-9,]+\}([-_a-zA-Z0-9?+*])*)/,/^(?:\()/,/^(?:\))/,/^(?:[^()]*)/,/^(?:expr([ \t])*\()/,/^(?:\/)/,/^(?:\/)/,/^(?:\$?([_a-zA-Z])([_a-zA-Z0-9])*)/,/^(?:([-_a-zA-Z0-9?+*])+)/,/^(?:([-_a-zA-Z0-9?+*])*\[([-_a-zA-Z0-9^])+\]([-_a-zA-Z0-9?+*])*)/,/^(?:([-_a-zA-Z0-9?+*])*\{[_a-zA-Z0-9,]+\}([-_a-zA-Z0-9?+*])*)/,/^(?:([ \t])|([\x0a\x0d]))/,/^(?:=)/,/^(?:;)/,/^(?:\$)/,/^(?::)/,/^(?:,)/,/^(?:\.)/,/^(?:\()/,/^(?:\))/,/^(?:#.*)/,/^(?:!.*)/,/^(?:.|([\x0a\x0d])*)/,/^(?:\(\*)/,/^(?:\*\))/,/^(?:\(\*)/,/^(?:([ \t])+)/,/^(?:([\x0a\x0d]))/,/^(?:$)/,/^(?:.)/,/^(?:.)/],
conditions: {"OSCSECTION":{"rules":[29,30,31,32,33,34],"inclusive":false},"EXPRSECTION":{"rules":[24,25,26],"inclusive":false},"JSECTION":{"rules":[19,20],"inclusive":false},"COMMENT":{"rules":[45,46,47],"inclusive":false},"QSTR":{"rules":[15,16],"inclusive":false},"DQSTR":{"rules":[12,13],"inclusive":false},"INITIAL":{"rules":[0,1,2,3,4,5,6,7,8,9,10,11,14,17,18,21,22,23,27,28,35,36,37,38,39,40,41,42,43,44,48,49,50,51,52,53],"inclusive":true}}
});
return lexer;
})();
parser.lexer = lexer;
function Parser () {
  this.yy = {};
}
Parser.prototype = parser;parser.Parser = Parser;
return new Parser;
})();


if (typeof require !== 'undefined' && typeof exports !== 'undefined') {
exports.parser = INScoreParser;
exports.Parser = INScoreParser.Parser;
exports.parse = function () { return INScoreParser.parse.apply(INScoreParser, arguments); };
exports.main = function commonjsMain(args) {
    if (!args[1]) {
        console.log('Usage: '+args[0]+' FILE');
        process.exit(1);
    }
    var source = require('fs').readFileSync(require('path').normalize(args[1]), "utf8");
    return exports.parser.parse(source);
};
if (typeof module !== 'undefined' && require.main === module) {
  exports.main(process.argv.slice(1));
}
}
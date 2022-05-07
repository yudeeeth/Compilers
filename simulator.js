let DEBUG = false;
let fs = require('fs');
const { parse } = require('url');
let instructions = [];
(function readFile(file) {
    let fileContent = fs.readFileSync(file, 'utf8');
    let lines = fileContent.split('\n');
    lines.forEach(line => {
        instructions.push(line);
    });
})('out.md');

const debug = (...args) => {
    if(DEBUG)
    console.log(...args);
}

const print = (args)=>{
    if(typeof args === 'number'){
        args = args.toString();
    }
    process.stdout.write(args);
}

let labelmap = {};
let left  = 0;
for(let i = 0;i<instructions.length;i++){
    if(instructions[i]==""){
        continue;
    }
    if(instructions[i][0]!="\t"){
        labelmap[instructions[i].slice(0,-1)] = left;
        continue;
    }
    instructions[left] = instructions[i].slice(1).split(' ');
    if(instructions[left].length>2) {
        instructions[left][1] = instructions[left].slice(1).join(" ");
        instructions[left] = instructions[left].slice(0,2);
    }
    left++;
}
instructions = instructions.slice(0,left);
// console.table(instructions);
// console.table(labelmap);

// simulate
let stack = [];
let mem = {};
let fp = 0;
let retaddr = 0;
for(let ins =0;ins<instructions.length;ins++){
    let op = instructions[ins][0];
    let arg = instructions[ins][1];
    // print(op,arg,stack[stack.length-1]);
    // print("stack -> ",...stack);
    // print(instructions[ins]);
    let a,b;
    switch(op){
        case "decl": mem[arg] =  0;
            break;
        case "push": 
            if(arg=="ST"){
                a = stack.pop();
                stack.push(stack[a]);
            }
            else if(arg=="xFP"){
                stack.push(fp);
            }
            else if(arg[0]=="K")
                stack.push(mem[arg]);
            else 
                stack.push(parseFloat(arg));
            break;
        case "pop" : 
                    mem[arg] = stack.pop();
            break;
        case "print": 
                    if(instructions[ins].length==1)
                        {
                            arg = stack.pop();
                            print(arg);
                        }
                    else if(arg=='""')
                        print('\n');
                    else
                        print(arg.slice(1,-1));
            break;
        case "add": a = stack.pop();
                    b = stack.pop();
                    stack.push(a+b);
                    break;
        case "sub": a = stack.pop();
                    b = stack.pop();
                    stack.push(b-a);
                    break;
        case "mul": a = stack.pop();
                    b = stack.pop();
                    stack.push(a*b);
                    break;
        case "div": a = stack.pop();
                    b = stack.pop();
                    stack.push(b/a);
                    break;
        case "mod": a = stack.pop();
                    b = stack.pop();
                    stack.push(b%a);
                    break;
        case "eq":  a = stack.pop();
                    b = stack.pop();
                    stack.push(a==b?1:0);
                    break;
        case "neq": a = stack.pop();
                    b = stack.pop();
                    stack.push(a!=b?1:0);
                    break;
        case "gt":  a = stack.pop();
                    b = stack.pop();
                    stack.push(b>a?1:0);
                    break;
        case "lt":  a = stack.pop();
                    b = stack.pop();
                    stack.push(b<a?1:0);
                    break;
        case "geq": a = stack.pop();
                    b = stack.pop();
                    stack.push(b>=a?1:0);
                    break;
        case "leq": a = stack.pop();
                    b = stack.pop();
                    stack.push(b<=a?1:0);
                    break;
        case "jmp": ins = parseInt(labelmap[arg])-1;
                    // print(labelmap[arg]);
                    break;
        case "jeq": a = stack.pop();
                    b = stack.pop();
                    if(a==b){
                        ins = parseInt(labelmap[arg])-1;
                    }
                    break;
        case "jneq": a = stack.pop();
                    b = stack.pop();
                    if(a!=b){
                        ins = parseInt(labelmap[arg])-1;
                    }
                    break;
        case "call": 
                    // stack already has params, first thing to push is frame pointer
                    debug("stack size before call with args only->",stack.length);
                    stack.push(fp);
                    debug("pushing fp->",fp);
                    // set new fp
                    fp = stack.length - 1;
                    debug("new fp->",fp);
                    // push return address
                    stack.push(parseInt(ins)+1);
                    debug("return address->",ins+1);
                    ins = parseInt(labelmap[arg])-1;
                    debug("jump to/call->",ins);
                    // console.log(...stack);
                    break;
        case "ret" : 
                    let retval = parseInt(stack.pop());
                    debug("retval is->",retval);
                    retaddr = stack[fp+1];
                    debug("retaddr while returning->",retaddr);
                    let remfromstack = stack[fp+2];
                    debug("remove from stack->",remfromstack);
                    let oldfp = fp;
                    // remove excess shit on stack
                    fp = stack[fp];
                    debug("resetting fp->",fp);
                    stack = stack.slice(0,oldfp-remfromstack);
                    debug("remove from stack till->",oldfp-remfromstack+1)
                    ins = retaddr -1;
                    debug("stack size after returning w/o args->",stack.length);
                    stack.push(retval);
                    
                    break;
        
    }
}
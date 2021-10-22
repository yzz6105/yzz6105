//exports=module.exports
/*function add(a,b)
{
	return(a+b);
}
module.exports.add = add
//Instead of module you can just use exports
export.add = add
*/


exports.add=function(a,b)
{
	return a+b;
}

exports.sub=function(a,b)
{
	return a-b;
}

exports.mul = function(a,b)
{
	return a*b;
}

exports.div =function(a,b)
{
	return a/b;
}

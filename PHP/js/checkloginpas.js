const selectElement1 = document.querySelector('#UName');
const selectElement2 = document.querySelector('#UAge');
const selectElement3 = document.querySelector('#ULogin');
const selectElement4 = document.querySelector('#Upass');
selectElement1.addEventListener('change', (event) => {
  str = document.querySelector('#UName').value;
  const result1 = document.querySelector('.result1');
	if (str.match(/^[a-zA-ZА-Яа-я ]+$/)){
		result1.textContent = ``;
  }else{
	result1.textContent = `input normal name`;  
  }
});
selectElement2.addEventListener('change', (event) => {
  str = document.querySelector('#UAge').value;
  const result2 = document.querySelector('.result2');
  if (str.match(/^[0-9]+$/)){
	result2.textContent = ``;
  }else{
	result2.textContent = `input normal age`
  }
});
selectElement3.addEventListener('change', (event) => {
  const result3 = document.querySelector('.result3');
  str = document.querySelector('#ULogin').value;
  if (str.match(/^[a-zA-Zа-яА-Я0-9]+$/)){
	result3.textContent = ``;
  }else{
	 result3.textContent = `For create login use ABC and 123`;
  }
});
selectElement4.addEventListener('change', (event) => {
  const result4 = document.querySelector('.result4');
  str = document.querySelector('#Upass').value;
  if (str.match(/^[a-zA-Zа-яА-Я0-9]+$/)){
	result4.textContent = ``;
  }else{
	 result4.textContent = `For create password use ABC and 123`;
  }
});

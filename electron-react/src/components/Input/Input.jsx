import React, { useState } from 'react';

import './input.scss';

const Input = ({ compile }) => {
  const [code, setCode] = useState('');

  return (
    <div className='input__container'>
      <h1>Please enter your program</h1>

      <button className='button-3' onClick={() => compile(code)}>
        Compile
      </button>

      <textarea
        value={code}
        onChange={(event) => setCode(event.target.value)}
        cols='100'
        rows='35'
        spellcheck='false'
      ></textarea>
    </div>
  );
};

export default React.memo(Input);

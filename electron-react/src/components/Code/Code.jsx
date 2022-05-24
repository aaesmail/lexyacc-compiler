import React from 'react';

import './code.scss';

const Code = ({ title, code }) => {
  const lines = code.split('\n');

  for (let i = lines.length - 1; i >= 0; i--)
    if (!lines[i]) lines.splice(i);
    else break;

  const formatted = lines.map((line, i) => i + 1 + '  ' + line + '\n');

  return (
    <div>
      <h1>{title}</h1>

      <pre className='code__container'>{formatted}</pre>
    </div>
  );
};

export default React.memo(Code);

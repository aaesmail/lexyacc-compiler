import React, { Fragment, useCallback, useEffect } from 'react';

import Input from './components/Input';

const App = () => {
  useEffect(() => {
    electron.onCompileDone(({ code, compiledCode, symbolTable, errors }) => {
      console.log('Code', code);
      console.log('CompiledCode', compiledCode);
      console.log('SymbolTable', symbolTable);
      console.log('Errors', errors);
    });
  }, []);

  const compile = useCallback((code) => {
    electron.compile(code);
  });

  return (
    <Fragment>
      <Input compile={compile} />
    </Fragment>
  );
};

export default App;

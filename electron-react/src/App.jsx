import React, { Fragment, useState, useCallback, useEffect } from 'react';

import Input from './components/Input/Input';
import Loading from './components/Loading/Loading';

const App = () => {
  const [page, setPage] = useState('input');

  useEffect(() => {
    electron.onCompileDone(({ code, compiledCode, symbolTable, errors }) => {
      setPage('output');
    });
  }, []);

  const compile = useCallback((code) => {
    setPage('loading');
    electron.compile(code);
  });

  return (
    <Fragment>
      {page === 'input' && <Input compile={compile} />}
      {page === 'loading' && <Loading />}
      {page === 'output' && <div>output</div>}
    </Fragment>
  );
};

export default App;

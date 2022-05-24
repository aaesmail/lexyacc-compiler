import React, { Fragment, useState, useCallback, useEffect } from 'react';

import Input from './components/Input/Input';
import Loading from './components/Loading/Loading';
import Output from './components/Output/Output';

const App = () => {
  const [page, setPage] = useState('input');

  const [result, setResult] = useState({
    code: '',
    compiledCode: '',
    symbolTable: [],
    errors: [],
  });

  useEffect(() => {
    electron.onCompileDone(({ code, compiledCode, symbolTable, errors }) => {
      setResult({ code, compiledCode, symbolTable, errors });
      setPage('output');
    });
  }, [setResult, setPage]);

  const compile = useCallback(
    (code) => {
      setPage('loading');
      electron.compile(code);
    },
    [setPage]
  );

  const backToInput = useCallback(() => {
    setPage('input');
  }, [setPage]);

  return (
    <Fragment>
      {page === 'input' && <Input compile={compile} />}

      {page === 'loading' && <Loading />}

      {page === 'output' && (
        <Output
          back={backToInput}
          code={result.code}
          compiledCode={result.compiledCode}
          symbolTable={result.symbolTable}
          errors={result.errors}
        />
      )}
    </Fragment>
  );
};

export default React.memo(App);

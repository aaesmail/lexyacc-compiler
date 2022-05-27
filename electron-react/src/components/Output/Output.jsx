import React from 'react';

import './output.scss';

import Code from '../Code/Code';
import Table from '../Table/Table';

const Output = ({ back, code, compiledCode, symbolTable, errors }) => {
  return (
    <div className='output__container'>
      <div className='header'>
        <a className='next round' onClick={back}>
          &laquo; Back
        </a>
      </div>

      {symbolTable.length > 0 && <Table title={'Symbol Table'} table={symbolTable} />}

      {errors.length > 0 && <Table title={'Errors'} table={errors} />}

      {code && <Code title='Input Code' code={code} />}

      {compiledCode && <Code title='Compiled Code' code={compiledCode} />}
    </div>
  );
};

export default React.memo(Output);

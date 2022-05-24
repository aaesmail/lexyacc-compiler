import React from 'react';

import './table.scss';

const Table = ({ title, table }) => {
  const sortedTable = [...table].sort((a, b) => a.line - b.line);

  return (
    <div>
      <h1>{title}</h1>

      <table className='styled-table'>
        <thead>
          <tr>
            {Object.keys(sortedTable[0]).map((key, index) => (
              <th key={title + '-head-' + index}>{key}</th>
            ))}
          </tr>
        </thead>
        <tbody>
          {sortedTable.map((row, index) => (
            <tr key={title + '-row-' + index}>
              {Object.keys(row).map((key, index) => (
                <td key={title + '-item-' + index}>{row[key]}</td>
              ))}
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
};

export default React.memo(Table);

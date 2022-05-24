import React from 'react';

import './loading.scss';

const Loading = () => {
  return (
    <div className='loading__container'>
      <div className='lds-dual-ring'></div>
    </div>
  );
};

export default React.memo(Loading);

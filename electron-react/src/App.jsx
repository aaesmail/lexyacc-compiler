import React from 'react';

const App = () => {
  return (
    <div>
      <h1>I am App Component</h1>
      <button
        onClick={() => {
          electron.notificationApi.sendNotification('Hello from Electron');
        }}
      >
        Notify
      </button>
    </div>
  );
};

export default App;

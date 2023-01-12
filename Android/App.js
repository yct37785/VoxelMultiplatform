/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 * @flow strict-local
 */

import React from 'react';
import type {Node} from 'react';
import {
  SafeAreaView,
  ScrollView,
  StatusBar,
  StyleSheet,
  Text,
  useColorScheme,
  View,
} from 'react-native';
import { MyView } from './MyView';

const App: () => Node = () => {
  const isDarkMode = useColorScheme() === 'dark';

  return (
    <View style={{ flex: 1, backgroundColor: 'green' }}>
      <MyView />
    </View>
  );
};

export default App;

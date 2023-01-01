
DROP DATABASE IF EXISTS `test`;
CREATE DATABASE IF NOT EXISTS `test`;

CREATE TABLE `dht11` (
  `serial` int(11) NOT NULL,
  `humidity` int(11) NOT NULL,
  `temperature` int(11) NOT NULL,
  `lm35` float(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `dht11`
--
ALTER TABLE `dht11`
  ADD PRIMARY KEY (`serial`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `dht11`
--
ALTER TABLE `dht11`
  MODIFY `serial` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
COMMIT;


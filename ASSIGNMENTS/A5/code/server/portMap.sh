sudo iptables -A PREROUTING -t nat -p tcp --dport 80 -j REDIRECT --to-ports 1234

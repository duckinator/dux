qemu -s -S -fda image &
echo "Run \`gdb dux\`"
echo "In gdb:"
echo "  \`target remote :1234\` to access qemu"
echo "  \`break <symbol_name>\`, ie 'isr3' or 'kmain', to add a breakpoint"
echo "  \`c\` to continue execution, or \`n\` to go to next instruction and stop"
echo "  \`p\` to get variable information"

using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace TestDllGUI
{
    public partial class Form1 : Form
    {
        [DllImport("/Go-DLL/DLL/mydll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr SayHello(string name);

        [DllImport("/Go-DLL/DLL/mydll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Add(int a, int b);

        private Button buttonSayHello;
        private Button buttonAdd;
        private Label resultLabel;

        public Form1()
        {
            InitializeComponent();
            InitializeCustomComponents();
        }

        private void InitializeCustomComponents()
        {
            buttonSayHello = new Button() { Text = "Say Hello", Location = new System.Drawing.Point(15, 15) };
            buttonAdd = new Button() { Text = "Add", Location = new System.Drawing.Point(15, 45) };
            resultLabel = new Label() { Location = new System.Drawing.Point(15, 75), AutoSize = true };

            buttonSayHello.Click += new EventHandler(ButtonSayHello_Click);
            buttonAdd.Click += new EventHandler(ButtonAdd_Click);

            Controls.Add(buttonSayHello);
            Controls.Add(buttonAdd);
            Controls.Add(resultLabel);
        }

        private void ButtonSayHello_Click(object sender, EventArgs e)
        {
            string name = "C# GUI";
            IntPtr messagePtr = SayHello(name);
            string message = Marshal.PtrToStringAnsi(messagePtr);
            resultLabel.Text = message;
            Marshal.FreeHGlobal(messagePtr); // Free the memory allocated by the DLL
        }

        private void ButtonAdd_Click(object sender, EventArgs e)
        {
            int result = Add(3, 4);
            resultLabel.Text = "Result of Add: " + result;
        }
    }
}

